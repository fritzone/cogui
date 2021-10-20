#include "radiobutton.h"
#include "radiobutton_group.h"

cogui::radiobutton_group::~radiobutton_group()
{
    for(auto& b : m_buttons)
    {
        delete b;
    }
}

int cogui::radiobutton_group::calculate_width() const
{
    return calculate_width(m_buttons);
}

int cogui::radiobutton_group::calculate_height() const
{
    return calculate_height(m_buttons);
}

const std::vector<cogui::radiobutton*> &cogui::radiobutton_group::buttons() const
{
    return m_buttons;
}

int cogui::radiobutton_group::calculate_height(const std::vector<cogui::radiobutton*>& buttons) const
{
    int calc_height = 0;

    for(const auto& r : buttons)
    {
        calc_height +=desktop::get().get_theme()->minimum_radiobutton_height(*r);
    }

    return calc_height + 2; // frame around top/bottm

}

int cogui::radiobutton_group::calculate_width(const std::vector<cogui::radiobutton*> &buttons) const
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


void cogui::radiobutton_group::click(int x, int y)
{
    log_info() << "RBG click:" << x << "," << y << "top=" << this->get_y();
    // find the item under (x,y)
    auto idx = y - this->get_y();
    if(idx < m_buttons.size())
    {
        if(m_selected_idx > -1)
        {
            if(m_selected_idx == idx)
            {
                m_buttons[idx]->check();
                return;
            }
            m_buttons[m_selected_idx]->uncheck();
        }

        m_selected_idx = idx;
        state_changer::set_state(this, idx);
        m_buttons[m_selected_idx]->check();
    }

}

