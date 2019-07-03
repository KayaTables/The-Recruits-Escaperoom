// Hier worden variabelen gedeclareerd:
// in dit geval welke IO-pin bij welke input hoort.
int sleutelschakelaar = 57; //I0.5
int meterkast = 56; //I0.4
int checkschuif = 55; //I0.3
int codealarm = 54; //I0.2
int checktelefoon = 3; //I0.1
int checkbalie = 2; //I0.0

int checkluikjeHEL = 63; //I1.5
int checkkast = 62; //I1.4
int twister1 = 61; //I1.3
int twister2 = 60; //I1.2
int lasers = 19; //I1.1
int bardeur = 18; //I1.0

int twister5 = 69; //I2.5
int twister6 = 68; //I2.4
int toestskluis1 = 67;//I2.3
int toestskluis2 = 66;//I2.2
int toestskluis3 = 21;//I2.1


int Ins[17] = {sleutelschakelaar, meterkast, checkschuif, codealarm, checktelefoon,
               checkbalie, checkluikjeHEL, checkkast, twister1, twister2, lasers,
               bardeur, twister5, twister6, toestskluis1, toestskluis2, toestskluis3
              };

String Insstr[17] = {"sleutelschakelaar", "meterkast", "checkschuif", "codealarm", "checktelefoon",
                     "checkbalie", "checkluikjeHEL", "checkkast", "twister1", "twister2", "lasers",
                     "twister4", "twister5", "twister6", "toestskluis1", "toestskluis2", "toestskluis3"
                    };

// En hier welke IO-pin (verbonden met een relais) bij welke magneet/output
int kleefschuif = 37; //R0.8
int motorschuif = 38; //R0.7
int alarmlicht = 39; //R0.6
int alarmbel = 40; //R0.5
int LED = 24; //R0.4

int telefoongeluid = 42; //R1.8
int kleefbuizenpost = 43; //R1.7
int kleefbalie = 44; //R1.6
int kleefluik = 45; //R1.5
int stroborookmachine = 32; //R1.4

int kleefkantoor = 47; //R2.8
int LEDjekantoor = 48; //R2.7
int kleefkluis1 = 49; //R2.6
int kleefkluis2 = 34; //R2.4

int steegrook = 35; //R2.3

int kleefkluis3 = 25; //R0.3


// Hier zijn variabelen gedeclareerd die aangeven of digitale sensoren een
// I/O terug geven. (I is dicht, O open)
boolean DIOs[17]; //Digital IO state

//Digital IO startstate
boolean DIOst[17] = {1, //0 IOsleutelschakelaar
                     0, //1 IOmeterkast
                     1, //2 IOcheckschuif
                     0, //3 IOcodealarm
                     1, //4 IOchecktelefoon
                     1, //5 IOcheckbalie
                     1, //6 IOcheckluikjeHEL
                     1, //7 IOcheckkast
                     0, //8 IOtwister1
                     0, //9 IOtwister2
                     0, //10 IOlasers
                     0, //11 IObardeur
                     0, //12 IOtwister5
                     0, //13 IOtwister6
                     0, //14 IOtoestskluis1
                     0, //15 IOtoestskluis2
                     0
                    };  //IOtoestskluis3

boolean DIOch[17]; //Digital IO has been changed
boolean DIObf[17]; //Digital IO change buffer


//  Voor de serial communication is er een variabele nodig om tijdelijk
//  uitleesinformatie in op te slaan.
int incomingByte = 0;

int fase = 0;

boolean doordone = 0;

float tfase[17];

// filter
int fltr[17]; // filter starting time
int buffertime = 200; // filter buffer time

boolean meterkastb = false;
boolean lasersb = false;
boolean codeob = false;
boolean codebb = false;

// Eerst wordt hier een setup method gedraait:
// - de pins worden geinitialiseerd als ins/outputs
// - de serial communication wordt geinitialisserd met de gewenste baudrate (schrijfsnelheid)
// (de serial port, waar de serial communication binnen komt,
// kun je checken met de serial monitor (Tools - Serial monitor/ (Ctrl-Shift-m))
void setup() {
  // Initialiseer de deursensoren ed als inputs
  pinMode(sleutelschakelaar, INPUT);
  pinMode(meterkast, INPUT);
  pinMode(checkschuif, INPUT);
  pinMode(codealarm, INPUT);
  pinMode(checktelefoon, INPUT);
  pinMode(checkbalie, INPUT);

  pinMode(checkluikjeHEL, INPUT);
  pinMode(checkkast, INPUT);
  pinMode(twister1, INPUT);
  pinMode(twister2, INPUT);
  pinMode(lasers, INPUT);
  pinMode(bardeur, INPUT);

  pinMode(twister5, INPUT);
  pinMode(twister6, INPUT);
  pinMode(toestskluis1, INPUT);
  pinMode(toestskluis2, INPUT);
  pinMode(toestskluis3, INPUT);


  // Initiaseer de magneten en outputs als outputs
  pinMode(kleefschuif, OUTPUT);
  pinMode(motorschuif, OUTPUT);
  pinMode(alarmlicht, OUTPUT);
  pinMode(alarmbel, OUTPUT);
  pinMode(LED, OUTPUT);

  pinMode(telefoongeluid, OUTPUT);
  pinMode(kleefbuizenpost , OUTPUT);
  pinMode(kleefbalie, OUTPUT);
  pinMode(kleefluik, OUTPUT);
  pinMode(stroborookmachine, OUTPUT);

  pinMode(kleefkantoor , OUTPUT);
  pinMode(LEDjekantoor, OUTPUT);
  pinMode(kleefkluis1, OUTPUT);
  pinMode(kleefkluis2, OUTPUT);

  pinMode(steegrook, OUTPUT);

  pinMode(kleefkluis3, OUTPUT);

  // Initialiseer de serial communication op 9600 (standaard)
  Serial.begin(9600);
  // Hier wordt naar de serial port geschreven dat de variabelen en pins zijn geinitieerd
  // ("\n" geeft aan naar de volgende regel gaan.)
  Serial.write("Variabelen en pins zijn geinitieerd.");
  Serial.write("\n");

  // De startwaardes van de outputs worden hier ook aangegeven en uitgeschreven
  // Alle magneten moeten aan het begin bijvoorbeeld aan staan
  digitalWrite(kleefschuif, HIGH);
  digitalWrite(kleefbuizenpost, HIGH);
  digitalWrite(kleefbalie, LOW);
  digitalWrite(kleefluik, HIGH);
  digitalWrite(kleefkantoor, HIGH);
  digitalWrite(kleefkluis1, HIGH);
  digitalWrite(kleefkluis2, HIGH);
  digitalWrite(kleefkluis3, HIGH);

  // Als deurtje van de sleutelschakelaar open staat. Waarschuwen!
  //if (digitalRead(sleutelschakelaar)==0){
  // Serial.println("Deurtje van de sleutel staat nog open");
  // delay(2000);
  //}


  // Als schuif open dan dichtmaken
  // if (digitalRead(checkschuif)==0){
  //    digitalWrite(motorschuif, HIGH);
  //   Serial.println("De schuifdeur was open");
  //   delay(500);
  //   digitalWrite(motorschuif, LOW);
  // }

  // Rest outputs uitzetten voor de zekerheid
  digitalWrite(alarmlicht, LOW);
  digitalWrite(alarmbel, LOW);
  digitalWrite(LED, LOW);
  digitalWrite(telefoongeluid, LOW);
  digitalWrite(stroborookmachine, LOW);
  digitalWrite(LEDjekantoor, LOW);
  digitalWrite(steegrook, LOW);



  // Hier wordt naar de serial port geschreven dat de startwaardes van de run klaar zijn
  Serial.write("Startwaardes outputs zijn uitgevoerd.");
  Serial.write("\n");
  Serial.write("\n");

  // Hier worden de instructies naar de serial port geschreven voor het simpele
  // programmaatje waarmee je de escape room kan besturen/ checken
  Serial.write("Kies een van de volgende opties door het cijfer in te typen gevolgd door ENTER:");
  Serial.write("\n");
  Serial.write("1. Check alle sensoren status nu.");
  Serial.write("\n");
  Serial.write("2. Check welke sensoren verandering hebben gemerkt.");
  Serial.write("\n");
  Serial.write("3. Check voortgang team.");
  Serial.write("\n");
  Serial.write("4. Handmatig naar de volgende fase gaan.");
  Serial.write("\n");
  DIOch[7] = 0;
}

// Nu wordt de loop method gerund, de hoofdcode, die zodra hij klaar is opnieuw begint
// Eerst lezen we telkens uit wat er met de sensoren is gebeurt,
// dan bepalen we of er een verandering in de voortgang is (in welke 'state' het systeem
// zich bevind) en tot slot wat er moet gebeuren als dat het geval is.
void loop() {

  // Eerst dus alle sensoren uitlezen
  for (int i = 0; i < 17; i++) {
    DIOs[i] = digitalRead(Ins[i]);
    //delay(5);
    //Serial.print(DIOs[i]); Serial.print("   ");
    //Check of klopt met startwaarde
  //  if ((DIOs[i] != DIOst[i]) && (DIOch[i] == 0)) {
    //  DIOch[i] = 1;
   // }
   // if (DIOch[2] == 1 && DIOch[0] == 0) {
    //  DIOch[2] = 0;
   // }
    if ((DIOs[i] != DIOst[i]) && (DIOch[i] == 0)) {
      delay(buffertime);
      DIOs[i] = digitalRead(Ins[i]);
      if ((DIOs[i] != DIOst[i]) && (DIOch[i] == 0)) {
        DIOch[i] = 1;
      }
    }
  }
 

  //Serial.println(" ");
  // los van volgorde als bardeur open en schuifdeur open dan schuifdeur dicht
  if (fase > 3 && !doordone && DIOs[2] == 0 && DIOs[11] == 0) {
    //motorschuif even aan

    digitalWrite(motorschuif, HIGH);
    delay(1000);
    digitalWrite(motorschuif, LOW);
    Serial.println("Schuifdeur is dicht.");
    //delay(5000);
    doordone = 1;

  }

  //meterkast staat los van fases
  if (DIOs[1] == 1) { //meterkast is omgezet
    //Serial.println("Meterkast is omgezet.");
    //tfase[1] = millis()/1000;
    //LED gaat aan
    digitalWrite(LED, HIGH);
    //Serial.println("Het licht is aangegaan.");
  }
  if (DIOs[1] == 0) { //meterkast is omgezet
    //Serial.println("Meterkast is omgezet.");
    //tfase[1] = millis()/1000;
    //LED gaat aan
    digitalWrite(LED, LOW);
    //Serial.println("Het licht is aangegaan.");
  }
  //fase 1
  if (fase == 0 &&  DIOch[0] == 1) { //Deurtje is geopend
    Serial.println("Deurtje is geopend.");
    fase = 1;
    tfase[0] = millis() / 1000;
    DIOch[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17] = 0;
    //kleefschuif uit
    digitalWrite(kleefschuif, LOW);
    Serial.println("Kleefmagneet schuifdeur is uit.");
    delay(1000);

  }

  //fase 11
  if (fase == 1 &&  DIOch[2] == 1) { //Schuifdeur wordt geopend hierdoor gaat het alarm af.
    Serial.println("Schuifdeur is geopend");
    fase = 2;
    tfase[0] = millis() / 1000;

    /* Kaya: Dit alarm moet niet meer af gaan op dit moment
    //Alarm licht en geluid gaat aan na 5 seconde
    delay(5000);
    digitalWrite(alarmlicht, HIGH);
    digitalWrite(alarmbel, HIGH);
    Serial.println("Alarm is aan.");
    DIOch[3] = 0;
    DIObf[3] = 0;
    */
  }

  //fase 3
  if (fase == 2 &&  DIOch[3] == 1) { //alarmcode is ingetypt
    Serial.println("Alarmcode is correct ingevoerd.");
    fase = 3;
    tfase[2] = millis() / 1000;

    //Alarm licht en geluid gaan uit
    digitalWrite(alarmlicht, LOW);
    digitalWrite(alarmbel, LOW);
    Serial.println("Alarm is uit.");

    //na een paar seconden gaat de telefoon
    delay(6000);
    digitalWrite(telefoongeluid, HIGH);
    Serial.println("De telefoon moet nu gaan.");

    //voor de zekerheid telefoon op 0
    DIOch[4] = 0;
    DIObf[4] = 0;
  }

  //fase 4
  if (fase == 3 &&  DIOch[4] == 1) { //telefoon wordt opgenomen
    Serial.println("Telefoon is opgenomen.");
    fase =4 ;
    tfase[3] = millis() / 1000;

    // telefoon houd op met rinkelen
    digitalWrite(telefoongeluid, LOW);
    Serial.println("De telefoon houd op met rinkelen.");

    // er wordt nu over de telefoon gepraat
    Serial.println("Nu wordt er 20s over de telefoon gepraat.");
    delay(5 * 1000);

    //dan valt de buizenpost
    digitalWrite(kleefbuizenpost, LOW);
    Serial.println("De buizenpost is gevallen.");
    delay(1000);
    DIOch[7] = 0;
    DIObf[7] = 0;
  }

  //fase 5
   if (fase==4 &&  DIOch[10]==1){ //ze hebben de lasers aan
     Serial.println("Ze hebben de lasers aan.");
     fase = 5;
     tfase[4] = millis()/1000;
  //

   }

  //fase 6
  if (fase == 5 &&  DIOch[5] == 1) { //de balie deur is geopend
    Serial.println("De baliedeur is geopend.");
    fase = 6;
    tfase[5] = millis() / 1000;

    //kleef luik moet uit
    digitalWrite(kleefluik, LOW);
    Serial.println("De magneet van het luik is uit.");

  }

  //fase 7
  if ((fase == 6 || fase == 4)&&  DIOch[7] == 1) { //het luik is geopend
    Serial.println("Het luik is geopend.");
    fase = 7;
    tfase[6] = millis() / 1000;

    //rook en strobo gaan aan na 6 seconden voor 2 seconden
    delay(6000);
    digitalWrite(stroborookmachine, HIGH);
    delay(2500);
    digitalWrite(stroborookmachine, LOW);
    Serial.println("De rookmachine en stroboscoop zijn afgegaan.");

  }

  // Kaya: dit zijn vermoedelijk de knoppen die nu in de schacht zitten
  //fase 8
  if (fase == 7 &&  DIOs[8] == 1 ) { //&& DIOs[9]==1 && DIOs[10]==1 && DIOs[11]==1 && DIOs[12]==1 && DIOs[13]==1){ //alle twisterknoppen zijn ingedrukt
    Serial.println("Alle twisterknoppen zijn ingedrukt.");
    fase = 10;
    tfase[7] = millis() / 1000;

    //Kantoor kleef gat los
    digitalWrite(kleefkantoor, LOW);
    Serial.println("De magneet van het kantoor is uit gegaan.");

    //LEDje kantoor gaat aan
    digitalWrite(LEDjekantoor, HIGH);
    Serial.println("Het LEDje van het kantoor is aan.");

    DIOch[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17] = 0;
    DIObf[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17] = 0;
  }

  //fase 9.1
  //  if ((fase == 8) &&  DIOch[14]==1 ){//Kluis onder open
  if (DIOch[14] == 1 ) { //Kluis onder open
    Serial.println("Kluis code onder is ingevoerd.");
    tfase[8] = millis() / 1000;
    //    fase=9;

    //Kantoor kleef gat los
    digitalWrite(kleefkluis1, LOW);
    Serial.println("De magneet van onderste kluis balk is uit gegaan.");

  }

  //fase 9.2
  // if ((fase == 8) &&  DIOch[15]==1 ){//Kluis boven open
  if (DIOch[15] == 1 ) { //Kluis boven open
    Serial.println("Kluis code boven is ingevoerd.");
    tfase[8] = millis() / 1000;
    //    fase=9;

    //Kantoor kleef gat los

    digitalWrite(kleefkluis2, LOW);
    Serial.println("De magneet van bovenste kluis balk is uit gegaan.");

  }

  //fase 10
  /*if (fase == 9 &&  DIOch[14]==1 &&  DIOch[15]==1){//Beide kluisbalken zijn open
     Serial.println("Beide kluis codes zijn ingevoerd.");
     tfase[10] = millis()/1000;
     fase++;
     digitalWrite(kleefkluis1, LOW);
     digitalWrite(kleefkluis2, LOW);

    }*/

  //fase 11
  if (fase == 10 &&  DIOch[16] == 1) { //De laatste deur is open.
    Serial.println("De laatste deur is open.");
    tfase[11] = millis() / 1000;
    fase++;
  }










  // Check voor Serial input
  if (Serial.available()) {
    incomingByte = Serial.read();
  }

  // Schrijf gewenste info
  // Schrijf DIO status nu
  if (incomingByte == 49) {
    incomingByte = 0;
    Serial.println("Status nu:");
    for (int i = 0; i < 17; i++) {
      Serial.print(Insstr[i] + " = " + DIOs[i] + ", " );
    }
    Serial.write("\n");
  }

  // Schrijf DIO veranderd
  if (incomingByte == 50) {
    incomingByte = 0;
    Serial.println("Verandering gemerkt:");
    for (int i = 0; i < 17; i++) {
      Serial.print(Insstr[i] + " = " + DIOch[i] + ", " );
    }
    Serial.write("\n");
  }

  // Schrijf fase team met tijd
  if (incomingByte == 51) {
    incomingByte = 0;
    Serial.println("Fase waar het team zich in begeeft:");

    Serial.println("Fase is nu " + String(fase) + ", en tijd nu is " + String((float)millis() / 1000));
    for (int i = 0; i < fase; i++) {
      Serial.println("Fase " + String(i) + " duurde " + (String)tfase[i]);
    }
    Serial.write("\n");
  }

  // Naar volgende fase
  if (incomingByte == 52) {
    incomingByte = 0;
    fase++;

    Serial.println("Nieuwe fase is nu " + String(fase) + ".");
    Serial.write("\n");
  }

  if (incomingByte == 53) {
    incomingByte = 0;
    DIOch[2] = 0;
    digitalWrite(motorschuif, HIGH);
    Serial.println("De schuifdeur is geopend/dicht gemaakt.");
    delay(500);
    digitalWrite(motorschuif, LOW);
  }








}
