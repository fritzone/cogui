#include "layout.h"
#include "container.h"

void cogui::layout::horizontal::arrange_controls(std::vector<std::shared_ptr<cogui::control> >& controls,
                                                 cogui::container * cont)
{
    int width = cont->getWidth();
    int recommended_width = width / controls.size() - 1;
    int cx = 1;
    bool expandable = (m_expanded_column != -1);
    bool hiding = false;
    int last_x = 0;
    info() << "Expandable:" << expandable;
    int last_x_before_split = 0;

    if(expandable)
    {
        int accumulated_width = 0;
        for(int i = m_expanded_column; i<controls.size(); i++)
        {
            accumulated_width += controls[i]->minimumDrawableWidth() + 1; // +1 since the next control start +1
        }

        for(int i=0; i<controls.size(); i++)
        {
            if(i == m_expanded_column)
            {
                cx = cont->getWidth() - accumulated_width;
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
                c->setX(cx);
                c->setY(1);
                c->setHeight(cont->getHeight() - 2);

                c->setWidth(c->minimumDrawableWidth());
            }
            else
            {
                c->hide();
                if(cx > last_x_before_split)
                {
                    c->show();
                    c->setX(cx);
                    c->setY(1);
                    c->setHeight(cont->getHeight() - 2);

                    c->setWidth(c->minimumDrawableWidth());
                    hiding = false;
                }
            }

            cx += c->minimumDrawableWidth() + 1;
            last_x = cx;

        }
    }
    else
    {
        for (auto& c : controls)
        {
            c->show();
            c->setX(cx);
            c->setY(1);
            c->setHeight(cont->getHeight() - 2);
            c->setWidth(recommended_width - 1);
            cx += recommended_width + 1;
        }
    }
}

bool cogui::layout::horizontal::accept_new_size(const std::vector<std::shared_ptr<control>>&controls, int new_width, int new_height)
{
    int cx = 1;
    bool expandable = (m_expanded_column != -1);
    int last_used_x = -1;
    info() << "Expandable:" << expandable;

    if(expandable)
    {
        int accumulated_width = 0;
        for(int i = m_expanded_column; i<controls.size(); i++)
        {
            accumulated_width += controls[i]->minimumDrawableWidth() + 1; // +1 since the next control start +1
        }

        for(int i=0; i<controls.size(); i++)
        {
            if(i == m_expanded_column)
            {
                cx = new_width - accumulated_width;
                if(cx < last_used_x || cx < 0)
                {
                    return false;
                }
            }

            auto c = controls[i];
            last_used_x = cx + c->minimumDrawableWidth() + 1;
            cx += c->minimumDrawableWidth() + 1;

        }
    }

    return true;
}

void cogui::layout::horizontal::expand(int c)
{
    m_expanded_column = c;
    info() << "Setting expand cell:" << m_expanded_column;
    if(m_container)
    {
        debug() << "Relayouting";
        m_container->reLayout(m_container->getWidth(), m_container->getHeight(), true);
    }
}


void cogui::layout::vertical::arrange_controls(std::vector<std::shared_ptr<cogui::control> >& controls,
                                                 cogui::container * cont)
{
    int height = cont->getHeight();
    int recommended_height = height / controls.size() - 1;
    int cy = 1;
    bool expandable = (m_expanded_row != -1);
    int last_y = 0;
    bool hiding = false;
    int last_y_before_split = 0;

    if(expandable)
    {
        int accumulated_height = 0;
        for(int i = m_expanded_row; i<controls.size(); i++)
        {
            accumulated_height += controls[i]->minimumDrawableHeight() + 1; // +1 since the next control start +1
        }

        for(int i=0; i<controls.size(); i++)
        {

            if(i == m_expanded_row)
            {
                cy = cont->getHeight() - accumulated_height;
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
                c->setY(cy);
                c->setX(1);
                c->setWidth(cont->getWidth() - 1);

                c->setHeight(c->minimumDrawableHeight());
            }
            else
            {
                c->hide();
                if(cy > last_y_before_split)
                {
                    hiding = false;
                    c->show();
                    c->setY(cy);
                    c->setX(1);
                    c->setWidth(cont->getWidth() - 1);

                    c->setHeight(c->minimumDrawableHeight());
                }
            }
            cy += c->minimumDrawableHeight() + 1;
            last_y = cy;

        }
    }
    else
    {
        for (auto& c : controls)
        {
            c->show();

            c->setX(1);
            c->setY(cy);
            c->setHeight(recommended_height - 1);
            c->setWidth(cont->getWidth() - 1);

            cy += recommended_height + 1;
        }
    }
}

bool cogui::layout::vertical::accept_new_size(const std::vector<std::shared_ptr<cogui::control>>& controls, int new_width, int new_height)
{
    int cy = 1, last_used_y = -1;
    bool expandable = (m_expanded_row != -1);

    if(expandable)
    {
        int accumulated_height = 0;
        for(int i = m_expanded_row; i<controls.size(); i++)
        {
            accumulated_height += controls[i]->minimumDrawableHeight() + 1; // +1 since the next control start +1
        }

        for(int i=0; i<controls.size(); i++)
        {

            if(i == m_expanded_row)
            {
                cy = new_height - accumulated_height;
                if(cy <= last_used_y || cy < 0)
                {
                    return false;
                }
            }

            auto c = controls[i];
            last_used_y = cy + c->minimumDrawableHeight() + 1;
            cy += c->minimumDrawableHeight() + 1;
        }
    }
    return true;
}

void cogui::layout::vertical::expand(int c)
{
    m_expanded_row = c;
    info() << "Setting expand cell:" << m_expanded_row;
    if(m_container)
    {
        debug() << "Relayouting";
        m_container->reLayout(m_container->getWidth(), m_container->getHeight(), true);
    }
}

void cogui::layout::grid::arrange_controls(std::vector<std::shared_ptr<cogui::control> > &controls, cogui::container *cont)
{
    int width = cont->getWidth();
    int recommended_width = width / m_cols - 1;
    int cx = 1;
    int height = cont->getHeight();
    int recommended_height = height / m_rows - 1;
    int cy = 1;
    int rc = 0;
    int cc = 0;
    bool setting = true;
    for (auto& c : controls)
    {
        if(setting)
        {
            info() << "Setting:" << c << " at " << cx << "," << cy << " as " << rc << " - " << cc;

            c->setX(cx);
            c->setY(cy);
            c->setHeight(recommended_height - 1);
            c->setWidth(recommended_width - 1);
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
                    info() << "Stopped setting controls, switched to hiding them";
                    setting = false;
                }
            }
        }
        else
        {
            info() << "Hiding:" << c;
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
