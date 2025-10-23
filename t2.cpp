#include <SFML/Graphics.hpp>
#include <iostream>
#include <numbers>
using namespace std;


sf::VertexArray points(sf::PrimitiveType::Points);


void AddPoint(int x, int y)
{
    sf::Vertex v1;
    v1.position = sf::Vector2f(float(x), float(y));

    points.append(v1);
}

void swap(int& x, int& y)
{
    x += y;
    y = x - y;
    x -= y;
}

void myline(int x1, int y1, int x2, int y2, int c) {
    bool steep = abs(y2 - y1) > abs(x2 - x1);
    if (steep) {
        swap(x1, y1);
        swap(x2, y2);
    }
    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = abs(y2 - y1);
    int err = 0;
    int ystep = (y1 < y2) ? 1 : -1;

    for (; x1 != x2; x1++) {
        if (steep) AddPoint(y1, x1);
        else AddPoint(x1, y1);

        err += dy;
        if (err >= dx) {
            y1 += ystep;
            err -= dx;
        }
    }
}

void mycirc(int x0, int y0, int r, int c) {
    if (r < 0) return;
    int x = 0;
    int y = r;
    int d = 5/4 - r;

    while (x <= y) {
        AddPoint(x0 + x, y0 + y);
        AddPoint(x0 + y, y0 + x);
        AddPoint(x0 - y, y0 + x);
        AddPoint(x0 - x, y0 + y);
        AddPoint(x0 - x, y0 - y);
        AddPoint(x0 - y, y0 - x);
        AddPoint(x0 + y, y0 - x);
        AddPoint(x0 + x, y0 - y);

        x++;
        if (d < 0){
            d += 2 * x + 1;
        }
        else {
            y--;
            d += 2 * x - 2 * y + 2;
        }
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "LC");

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        myline(30, 40, 150, 1000, 200);
        mycirc(400, 400, 50, 0);

        window.clear();
        window.draw(points);
        window.display();
    }
}