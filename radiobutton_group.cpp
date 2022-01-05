#include "radiobutton.h"
#include "radiobutton_group.h"


void cogui::radiobutton_group::click(int x, int y)
{
    log_info() << "RBG click:" << x << "," << y << "top=" << this->get_y();
    // find the item under (x,y)
    auto idx = y - this->get_y();
    if(idx < m_controls.size())
    {
        if(m_selected_idx > -1)
        {
            if(m_selected_idx == idx)
            {
                m_controls[idx]->check();
                return;
            }
            m_controls[m_selected_idx]->uncheck();
        }

        m_selected_idx = idx;
        state_changer::set_state(this, idx);
        m_controls[m_selected_idx]->check();
    }

}
