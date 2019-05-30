#ifndef BRUSHLESS_H
#define BRUSHLESS_H

#include "Controller.h"

namespace Politocean
{
    namespace RPi
    {
        class Brushless
        {
            Controller& controller_;
            int pwmPin_;

            int velocity_;
        public:
            static const int MAX_PWM = 1580;
            static const int MIN_PWM = 1420;
            static const int ARM_PWM = 1500;

            Brushless(Controller& controller, int pwmPin) : controller_(controller), pwmPin_(pwmPin) {}

            void setup();
        };
    }
}

#endif // BRUSHLESS_H