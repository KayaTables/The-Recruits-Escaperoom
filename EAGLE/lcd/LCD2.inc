/**********************************************************************************/
//LCD 16X2 tipo 2 - WM-C1602M WINTEK
//Designed by Adriano Gandolfo
//Rev. 2.0 18/10/2008
/**********************************************************************************/
#macro LCD2_16X2(VALUE)
//Piazzola connettore
#macro PIAZZOLA()
union {
object{TOOLS_PCB_VIA(2,0.8,1,16,120,0)}
box{<-1,0,0><1,.1,2.5>}
texture { Silver_Metal}}
#end
//connettore femmmina 1x16
#macro BL_1X16()
object{BL_GRND(16,1)}
#end
//connettore maschio 1x16
#macro PH_1X16()
object{PH_GRND(1,16,0,2.54)}
#end 
// Basetta di base
union {
difference{
        box{<-8,0,2.54><72,-1.6,-33.46>}
        cylinder{<-5.5,-0,0>,<-5.5,-1.6,0>,2.5/2 open}
        cylinder{<-5.5,-0,0>,<-5.5,-1.6,0>,2.5/2 open translate<75,0,0>}
        cylinder{<-5.5,-0,0>,<-5.5,-1.6,0>,2.5/2 open translate<0,0,-31>}
        cylinder{<-5.5,-0,0>,<-5.5,-1.6,0>,2.5/2 open translate<75,0,-31>}      
texture {col_brd}}
//Esterno zona display 
difference{
object {
 Round_Box(<-4.6,0,-2.86>,<68.6,4.8,-28.06>, .5, 0)
   pigment{Gray10} finish { Shiny }
   //texture{col_silver} finish { phong 1}
 scale<1,1,1>
 rotate<0,0,0>
 translate<0,0,0>
}
box{<0.25,0,-7.96><64.25,5,-22.96>}
}
union {
box{<0.25,0,-7.96><64.25,4.6,-22.96>} pigment{color GreenYellow} finish {Shiny } }
//Testo LCD prima riga 16 caratteri
text {ttf global_fontfile_alphalcd "LCD16x2CARATTERI" 0, 0 pigment{Gray10} scale 4.9 rotate<90,0,0> translate<3.5,4.7,-14>}
//Testo LCD seconda riga 16 caratteri
text {ttf global_fontfile_alphalcd "www.adrirobot.it" 0, 0 pigment{Gray10} scale 4.9 rotate<90,0,0> translate<3.5,4.7,-20.05>}
//Numeri pin
text{ttf besch_font "1" 0,0 pigment{White} scale 2 rotate<90,0,0> translate<-2.5,.2,0>}
text{ttf besch_font "16" 0,0 pigment{White} scale 2 rotate<90,0,0> translate<40,.2,0>}
//Sigla produttore
text{ttf besch_font "WM-C1602M WINTEK" 0,0 pigment{White} scale 3 rotate<90,0,0> translate<30,.1,-32>}
object{PIAZZOLA()}
object{PIAZZOLA() translate<2.54,0,0>}
object{PIAZZOLA() translate<5.08,0,0>}
object{PIAZZOLA() translate<7.62,0,0>}
object{PIAZZOLA() translate<10.16,0,0>}
object{PIAZZOLA() translate<12.7,0,0>}
object{PIAZZOLA() translate<15.24,0,0>}
object{PIAZZOLA() translate<17.78,0,0>}
object{PIAZZOLA() translate<20.32,0,0>}
object{PIAZZOLA() translate<22.86,0,0>}
object{PIAZZOLA() translate<25.4,0,0>}
object{PIAZZOLA() translate<27.94,0,0>}
object{PIAZZOLA() translate<30.48,0,0>}
object{PIAZZOLA() translate<33.02,0,0>}
object{PIAZZOLA() translate<35.56,0,0>}
object{PIAZZOLA() translate<38.1,0,0>}
//connetore maschio 
object{PH_1X16() translate<19.05,1.6,0> rotate <180,0,0>}
//connettore femmina
object{BL_1X16() translate<19.05,-11.6,0> }
}
#end