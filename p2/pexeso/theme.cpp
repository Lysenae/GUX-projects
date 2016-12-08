#include "theme.h"

Theme::Theme()
{
    m_theme = THEME_NONE;
}

void Theme::set(int theme)
{
    switch(theme)
    {
        case 1:
            m_theme = THEME_ANIMALS;
            break;
        case 2:
            m_theme = THEME_NATURE;
            break;
        case 3:
            m_theme = THEME_FRUIT;
            break;
        default:
            m_theme = THEME_NONE;
            break;
    }
}

ThemeType Theme::get()
{
    return m_theme;
}

QPixmap Theme::loadImage(int i)
{
    if(i >= 0 && i <= 18 && m_theme != THEME_NONE)
    {
        QString s = ":images/";
        if(m_theme == THEME_ANIMALS)
            s += "a";
        else if(m_theme == THEME_NATURE)
            s += "n";
        else if(m_theme == THEME_FRUIT)
            s += "f";
        s += QString::number(i);
        return QPixmap(s).scaled(50, 50);
    }

    return QPixmap();
}
