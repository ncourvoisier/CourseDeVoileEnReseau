#ifndef SAILINSANE_BOATCONTROLLER_H
#define SAILINSANE_BOATCONTROLLER_H

#include <cmath>
#include <gf/Time.h>

#include "Boat.h"
#include "../Protocol.h"
#include "World.h"

namespace sail
{

    class BoatController
    {
    public:
        BoatController(World& world);

        void processPlayerAction(Boat& boat, const PlayerAction& action);
        bool updateBoatPosition(Boat& boat, gf::Time dt);

    private:
        void moveRudderRight(Boat& boat);
        void moveRudderLeft(Boat& boat);
        void centerRudder(Boat& boat);
        void sheetOut(Boat& boat);
        void sheetIn(Boat& boat);

        bool isOnLand(double x, double y);

    private:
        World& m_world;

        static constexpr int RudderStepsNumber = 10;
        static constexpr int SheetStepsNumber = 10;

        static constexpr double RudderMaxAngle = M_PI_4;
        static constexpr double SheetMaxLength = 1.0;
        static constexpr double SheetMinLength = 0.0;

        static constexpr double RudderStep = RudderMaxAngle / RudderStepsNumber;
        static constexpr double SheetStep = (SheetMaxLength - SheetMinLength) / SheetStepsNumber;
    };

}

#endif //SAILINSANE_BOATCONTROLLER_H
