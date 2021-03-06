#ifndef SAILINSANE_WINDARROW_H
#define SAILINSANE_WINDARROW_H

#include <gf/Transformable.h>
#include <gf/VertexArray.h>

namespace sail
{

    class WindArrow: public gf::Transformable
    {
    public:
        WindArrow(double speed, double angle, double distanceToBoat);

        void draw(gf::RenderTarget &target, const gf::RenderStates &states) override;

    private:
        static constexpr double MaxDistance = 50;

        gf::VertexArray m_arrow;

        float m_speed;
        float m_direction;
    };

}

#endif //SAILINSANE_WINDARROW_H
