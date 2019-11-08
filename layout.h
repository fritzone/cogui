#ifndef LAYOUT_H
#define LAYOUT_H

#include <vector>
#include <memory>

namespace cogui {

class control;
class container;

namespace layout {

class abstract
{
public:
    virtual void arrange_controls(std::vector<std::shared_ptr<cogui::control>>&, container*) = 0;

    // this will be called before a window will resize itself
    // will calculate the size of the controls and if they add up for more than the new size
    // it will return false
    virtual bool accept_new_size(const std::vector<std::shared_ptr<cogui::control>>&, int, int ) = 0;

    container *getContainer() const;
    void setContainer(container *container);

protected:
    container* m_container = nullptr;
};

class horizontal  : public abstract
{
public:
    horizontal() = default;

    /**
     * @brief arrange_controls will arrange the controls in a horizontal layout inside the
     * given containers' limits
     */
    void arrange_controls(std::vector<std::shared_ptr<cogui::control>>&, container*) override ;

    /**
     * @brief accept_new_size Calculates the size of the controls this window has an decides if they
     * will fit in the new size of not
     * @param new_size the proposed new size
     * @return true if the current controls fit, false otherwise
     */
    bool accept_new_size(const std::vector<std::shared_ptr<cogui::control>>&, int new_width, int new_height) override;


    /**
     * @brief expand expands the given column. All the controls before will be aligned to the left
     * and all the controls after will be aligned to the right
     */
    void expand(int);

private:

    int m_expanded_column = -1;

};

class vertical : public abstract
{
public:
    vertical() = default;

    /**
     * @brief arrange_controls will arrange the controls in a horizontal layout inside the
     * given containers' limits
     */
    void arrange_controls(std::vector<std::shared_ptr<cogui::control>>&, container*) override ;

    bool accept_new_size(const std::vector<std::shared_ptr<cogui::control>>&, int new_width, int new_height) override;

    /**
     * @brief expand expands the given row. All the controls before will be aligned to the top
     * and all the controls after will be aligned to the bottom
     */
    void expand(int);

private:

    int m_expanded_row = -1;
};

class grid : public abstract
{
public:
    grid(int r, int c) : m_rows(r), m_cols(c)
    {}

    /**
     * @brief arrange_controls will arrange the controls in a horizontal layout inside the
     * given containers' limits
     */
    void arrange_controls(std::vector<std::shared_ptr<cogui::control>>&, container*) override ;
    bool accept_new_size(const std::vector<std::shared_ptr<cogui::control>>&, int, int) override {return true; }

private:
    int m_rows;
    int m_cols;
};

}
}

#endif // LAYOUT_H
