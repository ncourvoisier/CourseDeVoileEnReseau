#include <iostream>
#include "Physics.h"

namespace sail {

    void sailing_physics_update(Boat& boat, const Wind& wind, const double dt) {
        if (sail_is_bounds(boat)) {
            boat.setSheetLength(boat.getSheetLength() + dt * boat.getSailIsFree());
        }

        if (mainsheet_is_tight(boat,wind)) {
            boat.setSailAngle(atan(tan(apparent_wind_direction(boat, wind))));

            if (!fabs(boat.getSailAngle())) {
                boat.setSheetLength(fabs(boat.getSailAngle()));
            }
        } else {
            boat.setSailAngle(sign_of(sin(-apparent_wind_direction(boat, wind))) * boat.getSheetLength());
        }

        //longitude = x
        boat.setLongitude(boat.getLongitude() + ((delta_x(boat, wind) / R_EARTH) * (180 / M_PI) * dt));
        //latitude = y
        boat.setLatitude(boat.getLatitude() +
                         ((delta_y(boat, wind) / R_EARTH) * ((180 / M_PI) / cos(boat.getLatitude() * M_PI / 180)) * dt));

        //set rotational velocity
        boat.setRotationalVelocity(boat.getRotationalVelocity() + delta_rotational_velocity(boat, wind) * dt);
        boat.setVelocity(boat.getVelocity() + delta_velocity(boat, wind) * dt);
        boat.setAngle(boat.getAngle() + boat.getRotationalVelocity() * dt);

        //keep angle between 0 and 2*pi

        if (boat.getAngle() < 0) {
            boat.setAngle(boat.getAngle() + M_PI * 2);
        }

        boat.setAngle(fmod(boat.getAngle(),M_PI * 2));
    }

    double sign_of(double a) {
        if (a <= 0) {
            return -1;
        } else {
            return 1;
        }
    }

    double apparent_wind_x(const Boat& boat, const Wind& wind) {
        return wind.getSpeed() * cos(wind.getDirection() - boat.getAngle()) -
               boat.getVelocity();
    }

    double apparent_wind_y(const Boat& boat, const Wind& wind) {
        return wind.getSpeed() * sin(wind.getDirection() - boat.getAngle());
    }

    double apparent_wind_direction(const Boat& boat, const Wind& wind) {
        return atan2(apparent_wind_y(boat, wind), apparent_wind_x(boat, wind));
    }

    double apparent_wind_speed(const Boat& boat, const Wind& wind) {
        return sqrt(pow(apparent_wind_x(boat, wind), 2) + pow(apparent_wind_y(boat, wind), 2));
    }

    bool mainsheet_is_tight(const Boat& boat, const Wind& wind) {
        return cos(apparent_wind_direction(boat, wind)) + cos(boat.getSheetLength()) < 0;
    }

    double force_on_rudder(const Boat& boat, const Wind& wind) {
        return boat.getRudderLift() * boat.getVelocity() * sin(boat.getRudderAngle());
    }

    double force_on_sail(const Boat& boat, const Wind& wind) {
        return boat.getSailLift() * apparent_wind_speed(boat, wind) * sin(
                boat.getSailAngle() - apparent_wind_direction(boat, wind));
    }

    bool sail_is_bounds(const Boat& boat) {
        return boat.getSheetLength() > -M_PI_2 && boat.getSheetLength() < M_PI_2;
    }

    double delta_y(const Boat& boat, const Wind& wind) {
        return boat.getVelocity()
            * cos(boat.getAngle())
            + boat.getDriftCoefficient()
            * wind.getSpeed()
            * cos(wind.getDirection());
    }

    double delta_x(const Boat& boat, const Wind& wind) {
        return boat.getVelocity()
            * sin(boat.getAngle())
            + boat.getDriftCoefficient()
            * wind.getSpeed()
            * sin(wind.getDirection());
    }

    double delta_rotational_velocity(const Boat& boat, const Wind& wind) {
        return ((boat.getSailCenterOfEffort()
            - boat.getMastDistance()
            * cos(boat.getSailAngle()))
            * force_on_sail(boat, wind)
            - boat.getRudderDistance()
            * cos(boat.getRudderAngle())
            * force_on_rudder(boat, wind)
            - boat.getAngularFriction()
            * boat.getRotationalVelocity()
            * boat.getVelocity())
            / boat.getInertia();
    }

    double delta_velocity(const Boat& boat, const Wind& wind) {
        return (sin(boat.getSailAngle())
            * force_on_sail(boat, wind)
            /*- sin(boat.getRudderAngle()) // Modification aiming to let the boat move when it's rotating
            * force_on_rudder(boat, wind)*/
            - boat.getTangentialFriction()
            * boat.getVelocity()
            * boat.getVelocity())
            / boat.getMass();
    }

}
