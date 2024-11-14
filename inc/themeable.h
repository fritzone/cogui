#ifndef THEMEABLE_H
#define THEMEABLE_H

#include "control.h"
#include <memory>

namespace cogui {

template<class T>
struct themeable : public control
{
    struct executor_base
    {
        virtual int run() = 0;
    };

    template<class E>
    struct executor_wrapper : public executor_base
    {
        executor_wrapper( T* o, E f) : m_o(o), functor(f) {}

        int run() override
        {
            return functor(m_o);
        }

        T* m_o = nullptr;
        E functor;
    };

    template<class S, class DRAW, class MDW, class MDH>
    themeable(int x, int y, int width, int height, const S& title, T* o, DRAW drawer, MDW mdw, MDH mdh) :
        control(x, y, width, height, title),
        m_draw( new executor_wrapper<DRAW>(o, drawer)),
        m_minimum_object_width(new executor_wrapper<MDW>(o, mdw)),  m_minimum_object_height(new executor_wrapper<MDH>(o, mdh))
    {
    }

    int minimum_drawable_width() const override
    {
        return m_minimum_object_width->run();
    }

    int minimum_drawable_height() const override
    {
        return m_minimum_object_height->run();
    }

    void draw() const override
    {
        m_draw->run();
    }

private:

    std::shared_ptr<executor_base> m_draw;
    std::shared_ptr<executor_base> m_minimum_object_width;
    std::shared_ptr<executor_base> m_minimum_object_height;

};
}
#endif // THEMEABLE_H
