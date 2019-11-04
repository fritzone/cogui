#ifndef CONTAINER_H
#define CONTAINER_H

#include "control.h"
#include "button.h"
#include "layout.h"

#include <vector>
#include <iterator>
#include <memory>
#include <map>

namespace cogui {

class container : public control
{
public:
    container(int x, int y, int width, int height);

    template<typename ... Args>
    container(Args... args) : control (std::forward<Args>(args)...)
    {
    }

    button& add_button(int x, int y, int width, int height, const std::wstring& title);


    template<typename ... Args>
    button& add_button(int x, int y, int width, int height, const std::wstring& title, Args... args)
    {
        return *add_control<button>(x, y, width, height, this, title, std::forward<Args>(args)...);
    }

    void draw_content() const;
    void focus_next_element();
    void focus_element(std::shared_ptr<control> c);
    void press_element(std::shared_ptr<control> c);

    template<typename T, typename ... Args> T& setLayout(Args... args)
    {
        static_assert(std::is_base_of<cogui::layout::abstract, T>::value, "need a cogui::layout::abstract derived class");

        m_layout = std::make_shared<T>(std::forward<Args>(args)...);
        m_layout->setContainer(this);
        reLayout();

        return *(dynamic_cast<T*>(m_layout.get()));
    }

    void reLayout();

    /**
     * @brief element_under Will return the control which is under the X,Y pair
     * @param x - the X coordinate
     * @param y - the Y coordinate
     * @return the control to be found under the given coordinates, nullptr if nothing
     */
    std::shared_ptr<control> element_under(int x, int y);

    std::vector<std::shared_ptr<control>>::iterator& focused();

protected:

    void update_container();
    /*will just release a control that was pressed, helper function */
    void release_control(std::shared_ptr<control>);
private:

    /**
     * @brief The basic_store struct is the common place for all the controls
     * that need to be handled in a generic way.
     */
    struct basic_store
    {
        basic_store(container* c)
        {
            auto& cv = (container::m_container_stores)[c];
            cv.push_back(this);
        }

        virtual void draw() const = 0;
        virtual std::shared_ptr<control> element_under(int x, int y) = 0;

    protected:

        container* m_container;
    };

    /**
     * Each specific control has its own store
     */
    template <class C>
    struct store : public basic_store
    {
        store(container*c) : basic_store(c) {}

        // this contains the controls of this container
        std::vector<std::shared_ptr<C>> m_controls;

        void draw() const override
        {
            for(const auto& c : m_controls)
            {
                c->draw();
            }
        }

        std::shared_ptr<control> element_under(int x, int y) override
        {
            for(const auto& c : m_controls)
            {
                if(c->inside(x, y))
                {
                    return c;
                }
            }
            return std::shared_ptr<control>();
        }

    };

    /**
     * Adds a control to the container
     */
    template<typename C>
    std::shared_ptr<C> add_control(int x, int y, int width, int height, container* pc, const std::wstring& title = L"")
    {
        static store<C> cc(pc);
        cc.m_controls.emplace_back(std::make_shared<C>(x, y, width, height, title))->setParent(pc);

        auto shp = cc.m_controls.back();
        m_tab_order.push_back(shp);

        // invalidate the press and focused elements
        m_focused = m_tab_order.end();
        m_pressed = m_tab_order.end();
        m_prev_pressed = m_tab_order.end();

        return shp;
    }

    /**
     * Add a control with a set of forwarded arguments as slots for specific signals
     */
    template<typename C, typename ... Args>
    std::shared_ptr<C> add_control(int x, int y, int width, int height, container* pc,
                                   const std::wstring& title = L"", Args... args)
    {
        static store<C> cc(pc);
        cc.m_controls.emplace_back(std::make_shared<C>(x, y, width, height, title,
                                                       args...))->setParent(pc);

        auto shp = cc.m_controls.back();
        m_tab_order.push_back(shp);

        // invalidate the press and focused elements
        m_focused = m_tab_order.end();
        m_pressed = m_tab_order.end();
        m_prev_pressed = m_tab_order.end();

        return shp;
    }

protected:

    using CIT = std::vector<std::shared_ptr<control>>::iterator ;

    CIT m_focused = m_tab_order.end();   // the currently focused element
    CIT m_pressed = m_tab_order.end();   // the currently pressed element
    CIT m_prev_pressed = m_tab_order.end(); // the previously pressed element. Activated when the user pressed the button on a control and moved his mouse out of it

    std::vector<std::shared_ptr<control>> m_tab_order;    // the order for the focusable elements for this container only

private:

    static std::map<const container*, std::vector<basic_store*>> m_container_stores;
    std::shared_ptr<cogui::layout::abstract> m_layout;
};

}

#endif // CONTAINER_H
