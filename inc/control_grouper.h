#ifndef CONTROL_GROUPER_H
#define CONTROL_GROUPER_H

#include <initializer_list>
#include <memory>

namespace cogui
{

template<class C>
class control_grouper
{
public:

    control_grouper(const std::initializer_list<typename C::CREATOR>& controls)
    {
        for(const auto& rbc : controls)
        {
            std::shared_ptr<C> ptr_c;
            ptr_c.reset(rbc.get_control());
            m_controls.push_back(ptr_c);
        }
    }

    virtual ~control_grouper() = default;

    int calculate_width() const
    {
        return calculate_width(m_controls);
    }

    int calculate_height() const
    {
        return calculate_height(m_controls);
    }

    const std::vector<std::shared_ptr<C>> &controls() const
    {
        return m_controls;
    }

private:

    int calculate_height(const std::vector<std::shared_ptr<radiobutton>>& buttons) const
    {
        int calc_height = 0;

        for(const auto& r : buttons)
        {
            calc_height += desktop::get().get_theme()->minimum_radiobutton_height(*r);
        }

        return calc_height + 2; // frame around top/bottm

    }

    int calculate_width(const std::vector<std::shared_ptr<radiobutton>>& buttons) const
    {
        int max_width = -1;

        for(const auto& r : buttons)
        {
            int current_btn_width = desktop::get().get_theme()->minimum_radiobutton_width(*r);
            if(current_btn_width > max_width)
            {
                max_width = current_btn_width;
            }
        }

        return max_width + 4; // the space before/after text + the frame left/right
    }


protected:
    std::vector<std::shared_ptr<C>> m_controls;

};


}


#endif // CONTROL_GROUPER_H
