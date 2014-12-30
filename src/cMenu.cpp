
#include"Nucleo.cpp"
#include<SDL/SDL_ttf.h>

/*                             Constantes y variables globales                                 */
/***********************************************************************************************/


const Uint8 LIBERADO = 0;
const Uint8 PULSADO = 1;



/*                                 Prototipos de funciones                                     */
/***********************************************************************************************/

void Dibujar_Texto( SDL_Surface *Superficie, Uint16 *Texto, Uint16 x, Uint16 y, Uint8 Tam, SDL_Color Color );

class cMenu {
    private:
        char Cadenas[4][9];
        SDL_Surface *Opciones[4][2];
        SDL_Rect *Destinos[4][2];
        Uint8 Eleccion;
    public:
        cMenu();
        ~cMenu();
};

/*                                Definiciones de funciones                                    */
/***********************************************************************************************/
/*
cMenu::cMenu() : Eleccion(0) {

    TTF_Init();

    strcpy( Cadenas[0], "Jugar" );
    strcpy( Cadenas[1], "Ayuda" );
    strcpy( Cadenas[2], "Creditos" );
    strcpy( Cadenas[3], "Salir" );


    for( Uint8 i=0; i<4; i++ ){
        Opciones[i][LIBERADO] =
    }
};

cMenu::~cMenu(){
}

*/
void Dibujar_Texto( SDL_Surface *Superficie, Uint16 *Texto, Uint16 x, Uint16 y, Uint8 Tam, SDL_Color Color ){
    SDL_Surface *Superficie_Texto;

    TTF_Font *Fuente = TTF_OpenFont( "FONT/F1.ttf", Tam ); ;

    //Destino.x = x;
    //Destino.y = y;

    Superficie_Texto = TTF_RenderUNICODE_Solid( Fuente, Texto, Color );

    SDL_Rect Destino = { x, y, Superficie_Texto->w, Superficie_Texto->h };
    //Destino.w = Superficie_Texto->w;
    //Destino.h = Superficie_Texto->h;

    SDL_BlitSurface( Superficie_Texto, NULL, Superficie, &Destino );

    SDL_FreeSurface( Superficie_Texto );
    TTF_CloseFont( Fuente );
};
