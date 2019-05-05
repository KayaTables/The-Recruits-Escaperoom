/**********************************************************************************/
//LCD 16X2 tipo 1 - 162B Displaytech
//Designed by Adriano Gandolfo
//Rev. 2.0 18/10/2008
/**********************************************************************************/
#macro LCD1_16X2(VALUE)
//Piazzola connettore
#macro PIAZZOLA()
union {
object{TOOLS_PCB_VIA(2,0.8,1,16,120,0)}
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
        box{<-48.1,0,40.25><35.9,-1.6,-3.75>}
        cylinder{<-44.35,0,0>,<-44.35,-1.6,0>,2.5/2 open}//foro in basso a SX
        cylinder{<-44.35,0,0>,<-44.35,-1.6,0>,2.5/2 open translate<76.5,0,0>}//Foro in basso a DX
        cylinder{<-44.35,0,0>,<-44.35,-1.6,0>,2.5/2 open translate<-1,0,36.5>}//Foro in alto a SX
        cylinder{<-44.35,0,0>,<-44.35,-1.6,0>,2.5/2 open translate<77.5,0,36.5>}//Foro in alto a DX
        box{<-48.2,0.2,37.75><-45.35,-1.8,35.25>}//Finitura foro in alto a SX
        box{<-48.2,0.2,37.75><-45.35,-1.8,35.25> translate <81.3,0,0> }//Finitura foro in alto a DX      
texture {col_brd}}
//Esterno zona display 
difference{
object {
 Round_Box(<-42.95,0,32.25>,<30.75,5,7.45>, .5, 0)
   texture{col_silver} finish { phong 1}
 scale<1,1,1>
 rotate<0,0,0>
 translate<0,0,0>
}
box{<-39.3,0,27.85><26.7,5.01,11.2>}
}
//Interno zona display
union {
box{<-39.3,0,27.85><26.7,4.02,11.2>}
pigment{color GreenYellow} finish {Shiny }}
//Testo LCD prima riga 16 caratteri
text {ttf global_fontfile_alphalcd "LCD16x2CARATTERI" 1, 0 pigment{Gray10} scale 4.9 rotate<90,0,0> translate<-34.2,4.1,20.1>}
//Testo LCD prima riga 16 caratteri
text {ttf global_fontfile_alphalcd "www.adrirobot.it" 1, 0 pigment{Gray10} scale 4.9 rotate<90,0,0> translate<-34.2,4.1,14.2>}
//Numero pin
text{ttf besch_font "1" 1,0 pigment{White} scale 2 rotate<90,0,0> translate<-.5,.2,2>}
text{ttf besch_font "16" 1,0 pigment{White} scale 2 rotate<90,0,0> translate<-38.5,.2,2>}
//Sigla produttore
text{ttf besch_font "DISPLAYTECH 162B" 1,0 pigment{White} scale 3 rotate<90,0,0> translate<2,.1,3>}
object{PIAZZOLA()}
object{PIAZZOLA() translate<-2.54,0,0>}
object{PIAZZOLA() translate<-5.08,0,0>}
object{PIAZZOLA() translate<-7.62,0,0>}
object{PIAZZOLA() translate<-10.16,0,0>}
object{PIAZZOLA() translate<-12.7,0,0>}
object{PIAZZOLA() translate<-15.24,0,0>}
object{PIAZZOLA() translate<-17.78,0,0>}
object{PIAZZOLA() translate<-20.32,0,0>}
object{PIAZZOLA() translate<-22.86,0,0>}
object{PIAZZOLA() translate<-25.4,0,0>}
object{PIAZZOLA() translate<-27.94,0,0>}
object{PIAZZOLA() translate<-30.48,0,0>}
object{PIAZZOLA() translate<-33.02,0,0>}
object{PIAZZOLA() translate<-35.56,0,0>}
object{PIAZZOLA() translate<-38.1,0,0>}
//connetore maschio
object{PH_1X16() translate<-19.05,1.6,0> rotate <180,0,0>}
//connettore femmina
object{BL_1X16() translate<-19.05,-11.5,0> }
}
#end