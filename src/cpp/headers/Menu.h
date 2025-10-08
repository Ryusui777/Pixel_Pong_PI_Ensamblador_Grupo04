#pragma once 

#include "shared.h"
#include "Button.h"


class Menu {
    private:
        // Paths hacia todos los recursos graficos
        const char* bg_path = "res/menu/bg.png";
        const char* resume_path ="res/menu/resume.png";
        const char* home_path ="res/menu/home.png";

        // Members
        Texture2D blurBG;
        Button resumeButton;
        Button homeButton;

    public:
        /**
         * @brief Inicia los elementos de la clase,
         * carga sus texturas y posiciones.
         */
        void init();
        /**
         * @brief Rederiza el menu en pantalla
         */
        void draw();

};