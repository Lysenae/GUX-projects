#ifndef THEME_H
#define THEME_H

#include <QPixmap>
#include <QString>

#include <QDebug>

enum ThemeType
{
    THEME_NONE = 0,
    THEME_ANIMALS = 1,
    THEME_NATURE,
    THEME_FRUIT
};

class Theme
{
public:
    Theme();
    void set(int theme);
    ThemeType get();
    QString imageName(int i);
    QString toString();

private:
    ThemeType m_theme;
};

#endif // THEME_H
