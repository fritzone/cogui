#include "theme.h"
#include "cogui.h"
#include "menu.h"
#include "log.h"

cogui::rect cogui::theme::close_button_pos(const cogui::window &w)
{
	if(m_close_button_positions.count(&w) != 0)
	{
		return m_close_button_positions[&w];
	}
	return {};
}

cogui::rect cogui::theme::sysmenu_button_pos(const cogui::window &w)
{
	if(m_sysmenu_button_positions.count(&w) != 0)
	{
		return m_sysmenu_button_positions[&w];
	}
	return {};

}

void cogui::theme::update_menubar_positions(cogui::menu *m, std::pair<int, int> ul, std::pair<int, int> lr)
{
	m_menu_positions[m] = {ul.first, ul.second, lr.first - ul.first, lr.second - ul.second};
}

bool cogui::theme::current_menu_position_stored(const cogui::menu &m)
{
	return m_menu_positions.count(const_cast<menu*>(&m)) > 0;
}

cogui::rect cogui::theme::current_menu_position(const cogui::menu &m)
{
	return m_menu_positions[const_cast<menu*>(&m)];
}

void cogui::theme::set_window_close_button_position(const cogui::window &w, const cogui::rect &r)
{
	m_close_button_positions[&w] = r;
}

void cogui::theme::set_window_sysmenu_button_position(const cogui::window &w, const cogui::rect &r)
{
	m_sysmenu_button_positions[&w] = r;
}

void cogui::theme::set_window_maximize_button_position(const cogui::window &w, const cogui::rect &r)
{
//	log_info() << "Max at:" << r.x << "," << r.y;
	m_maximize_button_positions[&w] = r;
}

std::tuple<cogui::menu *, cogui::rect> cogui::theme::menu_at(int x, int y)
{
	for(auto& [m, p] : m_menu_positions)
	{
		log_info() << "Trying menu:" << m->caption() << "at (" <<p.x<<","<<p.y << ") - (" <<p.x + p.width<<","<<p.y + p.height<< ") has (" << x << "," << y << ")";
		if(p.x <=x && p.x + p.width>= x && p.y <= y && p.y + p.height >= y)
		{
			log_info() << "Found click:" << m->caption();
			return {m, p};
		}
	}
	return {nullptr, {}}	;
}


cogui::rect cogui::theme::maximize_button_pos(const cogui::window &w)
{
	if(m_maximize_button_positions.count(&w) != 0)
	{
		return m_maximize_button_positions[&w];
	}
	return {};

}
