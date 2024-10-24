#include "layout.h"
#include "container.h"
#include "window.h"
#include "button.h"
#include "desktop.h"

void cogui::layout::horizontal::arrange_controls(std::vector<std::shared_ptr<cogui::control> >& controls,
                                                 cogui::container * cont)
{
    int width = cont->get_width();
    int recommended_width = width / controls.size() - spacing() * controls.size();
    int cx = 1;
    bool expandable = (m_expanded_column != -1);
    bool hiding = false;
    int last_x = 0;
    log_info() << "Expandable:" << expandable;
    int last_x_before_split = 0;

    if(expandable)
    {
        int accumulated_width = 0;
		for(size_t i = m_expanded_column; i<controls.size(); i++)
        {
			accumulated_width += controls[i]->minimum_drawable_width() + 1; // +1 since the next control start +1
        }

		for(size_t i=0; i<controls.size(); i++)
        {
			if(i == static_cast<size_t>(m_expanded_column))
            {
                cx = cont->get_width() - accumulated_width;
                if(cx < 0 || cx < last_x)
                {
                    hiding = true;
                    last_x_before_split = last_x;
                }
                else
                {
                    hiding = false;
                }
            }

            auto c = controls[i];
            if(!hiding)
            {
                c->show();
                c->set_bounds(cx, cont->first_available_row(), c->minimum_drawable_width(), cont->get_height() - cont->first_available_row() - spacing());
            }
            else
            {
                c->hide();
                if(cx > last_x_before_split)
                {
                    c->show();
                    c->set_bounds(cx, cont->first_available_row(), c->minimum_drawable_width(), cont->get_height() - cont->first_available_row() - spacing());
                    hiding = false;
                }
            }

            cx += c->minimum_drawable_width() + 1;
            last_x = cx;

        }
    }
    else
    {
        for (auto& c : controls)
        {
            c->show();
            c->set_bounds(cx, cont->first_available_row(), recommended_width - spacing(), cont->get_height() - cont->first_available_row() - spacing());
            cx += recommended_width + spacing();
        }
    }
}

bool cogui::layout::horizontal::accept_new_size(const std::vector<std::shared_ptr<control>>&controls, int new_width, int )
{
    int cx = 1;
    bool expandable = (m_expanded_column != -1);
    int last_used_x = -1;
    log_info() << "Expandable:" << expandable;

    if(expandable)
    {
        int accumulated_width = 0;
		for(size_t i = m_expanded_column; i<controls.size(); i++)
        {
            accumulated_width += controls[i]->minimum_drawable_width() + 1; // +1 since the next control start +1
        }

		for(size_t i=0; i<controls.size(); i++)
        {
			if(i == static_cast<size_t>(m_expanded_column))
            {
                cx = new_width - accumulated_width;
                if(cx < last_used_x || cx < 0)
                {
                    return false;
                }
            }

            auto c = controls[i];
            last_used_x = cx + c->minimum_drawable_width() + 1;
            cx += c->minimum_drawable_width() + 1;

        }
    }

    return true;
}

void cogui::layout::horizontal::expand(int c)
{
    m_expanded_column = c;
    log_info() << "Setting expand cell:" << m_expanded_column;
    if(m_container)
    {
        log_debug() << "Relayouting";
		m_container->relayout(m_container->get_width(), m_container->get_height(), true);
    }
}


void cogui::layout::vertical::arrange_controls(std::vector<std::shared_ptr<cogui::control> >& controls,
                                                 cogui::container * cont)
{

    int height = cont->get_height() - cont->first_available_row() - 1;
    int recommended_height = height / controls.size() - spacing() * controls.size();
    int cy = cont->first_available_row() ;
    bool expandable = (m_expanded_row != -1);
    int last_y = 0;
    bool hiding = false;
    int last_y_before_split = 0;

    if(expandable)
    {
        int accumulated_height = 0;
		for(size_t i = m_expanded_row; i<controls.size(); i++)
        {
            accumulated_height += controls[i]->minimum_drawable_height() + 1; // +1 since the next control start +1
        }

		for(size_t i=0; i<controls.size(); i++)
        {
			if(i == static_cast<size_t>(m_expanded_row))
            {
                cy = cont->get_height() - accumulated_height;
                if(cy < 0 || cy < last_y)
                {
                    hiding = true;
                    last_y_before_split = last_y;
                }
                else
                {
                    hiding = false;
                }
            }

            auto c = controls[i];
            if(!hiding)
            {
                c->show();
                c->set_y(cy);
                c->set_x(1);
                c->set_width(cont->get_width() - 1);

                c->set_height(c->minimum_drawable_height());
            }
            else
            {
                c->hide();
                if(cy > last_y_before_split)
                {
                    hiding = false;
                    c->show();
                    c->set_y(cy);
                    c->set_x(1);
                    c->set_width(cont->get_width() - 1);

                    c->set_height(c->minimum_drawable_height());
                }
            }
            cy += c->minimum_drawable_height() + 1;
            last_y = cy;
        }
    }
    else
    {
        for (auto& c : controls)
        {
            c->show();

            c->set_x(1);
            c->set_y(cy);
            c->set_height(recommended_height - 1);
            c->set_width(cont->get_width() - 1);

            cy += recommended_height + 1;
        }
    }
}

bool cogui::layout::vertical::accept_new_size(const std::vector<std::shared_ptr<cogui::control>>& controls, int, int new_height)
{
    int cy = 1, last_used_y = -1;
    bool expandable = (m_expanded_row != -1);

    if(expandable)
    {
        int accumulated_height = 0;
		for(size_t i = m_expanded_row; i<controls.size(); i++)
        {
            accumulated_height += controls[i]->minimum_drawable_height() + 1; // +1 since the next control start +1
        }

		for(size_t i=0; i<controls.size(); i++)
        {

			if(i == static_cast<size_t>(m_expanded_row))
            {
                cy = new_height - accumulated_height;
                if(cy <= last_used_y || cy < 0)
                {
                    return false;
                }
            }

            auto c = controls[i];
            last_used_y = cy + c->minimum_drawable_height() + 1;
            cy += c->minimum_drawable_height() + 1;
        }
    }
    return true;
}

void cogui::layout::vertical::expand(int c)
{
    m_expanded_row = c;
    log_info() << "Setting expand cell:" << m_expanded_row;
    if(m_container)
    {
        log_debug() << "Relayouting";
		m_container->relayout(m_container->get_width(), m_container->get_height(), true);
    }
}

void cogui::layout::grid::arrange_controls(std::vector<std::shared_ptr<cogui::control> > &controls, cogui::container *cont)
{
    int width = cont->get_width();
    int recommended_width = width / m_cols - 1;
    int cx = 1;
    int height = cont->get_height();
    int cy = cont->first_available_row() ;
    int recommended_height = (height - cy) / m_rows - 1;
    int rc = 0;
    int cc = 0;
    bool setting = true;
    for (auto& c : controls)
    {
        if(setting)
        {
            c->set_x(cx);
            c->set_y(cy);
            c->set_height(recommended_height - 1);
            c->set_width(recommended_width - 1);
            c->show();

            cx += recommended_width + 1;
            cc ++;

            if(cc == m_cols)
            {
                cc = 0;
                cy += recommended_height + 1;
                cx = 1;
                rc ++;

                if(rc == m_rows)
                {
                    log_info() << "Stopped setting controls, switched to hiding them";
                    setting = false;
                }
            }
        }
        else
        {
            c->hide();
        }
    }
}

cogui::container *cogui::layout::abstract::getContainer() const
{
    return m_container;
}

void cogui::layout::abstract::setContainer(cogui::container *container)
{
    m_container = container;
}

int cogui::layout::abstract::spacing() const
{
    return m_spacing;
}

void cogui::layout::abstract::set_spacing(int s)
{
    m_spacing = s;
}
