// Adding all the auxiliary things here
#pragma once
#include "Button.h"
#include "State.h"
#include "Object.h"
#include "CMap.h"
#include "Collision.h"

#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
#include <iostream>
#include <math.h>

namespace st {
    struct Timer {
        sf::Clock mC;
        float runTime;
        bool bPaused;

        Timer() {
            bPaused = false;
            runTime = 0;
            mC.restart();
        }

        void Reset() {
            mC.restart();
            runTime = 0;
            bPaused = false;
        }

        void Start() {
            if (bPaused) {
                mC.restart();
            }
            bPaused = false;
        }

        void Pause() {
            if (!bPaused) {
                runTime += mC.getElapsedTime().asSeconds();
            }
            bPaused = true;
        }

        float GetElapsedSeconds() {
            if (!bPaused) {
                return runTime + mC.getElapsedTime().asSeconds();
            }
            return runTime;
        }
    };
}

const int ROADHEIGHT = 150;
