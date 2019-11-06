#include "layout.h"
#include "container.h"

void cogui::layout::horizontal::arrange_controls(std::vector<std::shared_ptr<cogui::control> >& controls,
                                                 cogui::container * cont)
{
    int width = cont->getWidth();
    int recommended_width = width / controls.size() - 1;
    int cx = 1;
    bool expandable = (m_expanded_column != -1);

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
                cx = cont->getWidth() - accumulated_width;
            }

            auto c = controls[i];
            c->show();
            c->setX(cx);
            c->setY(1);
            c->setHeight(cont->getHeight() - 2);

            c->setWidth(c->minimumDrawableWidth());
            cx += c->minimumDrawableWidth() + 1;

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

void cogui::layout::horizontal::expand(int c)
{
    m_expanded_column = c;
    info() << "Setting expand cell:" << m_expanded_column;
    if(m_container)
    {
        debug() << "Relayouting";
        m_container->reLayout();
    }
}


void cogui::layout::vertical::arrange_controls(std::vector<std::shared_ptr<cogui::control> >& controls,
                                                 cogui::container * cont)
{
    int height = cont->getHeight();
    int recommended_height = height / controls.size() - 1;
    int cy = 1;
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
                cy = cont->getHeight() - accumulated_height;
            }

            auto c = controls[i];
            c->show();
            c->setY(cy);
            c->setX(1);
            c->setWidth(cont->getWidth() - 1);

            c->setHeight(c->minimumDrawableHeight());
            cy += c->minimumDrawableHeight() + 1;

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

void cogui::layout::vertical::expand(int c)
{
    m_expanded_row = c;
    info() << "Setting expand cell:" << m_expanded_row;
    if(m_container)
    {
        debug() << "Relayouting";
        m_container->reLayout();
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
