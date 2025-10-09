#include <SFML/Graphics.hpp>
#include <iostream>
#include <numbers>
using namespace std;


const double PI = 3.14159265358979323846;

sf::VertexArray lines(sf::PrimitiveType::Lines);

sf::Vector2f addV(const sf::Vector2f& a, const sf::Vector2f& b) { return { a.x + b.x, a.y + b.y }; }
sf::Vector2f subV(const sf::Vector2f& a, const sf::Vector2f& b) { return { a.x - b.x, a.y - b.y }; }
sf::Vector2f mulV(const sf::Vector2f& v, float s) { return { v.x * s, v.y * s }; }
sf::Vector2f perp90(const sf::Vector2f& v) { return { v.y, -v.x }; }

sf::Vector2f rotateV(const sf::Vector2f& v, double rad) {
    double c = std::cos(rad), s = std::sin(rad);
    return { float(v.x * c - v.y * s), float(v.x * s + v.y * c) };
}

static inline void appendLine(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    sf::Vertex v1;
    v1.position = p1;
    v1.color = sf::Color::White;
    lines.append(v1);

    sf::Vertex v2;
    v2.position = p2;
    v2.color = sf::Color::White;
    lines.append(v2);
}

void pifagor(int n, int x0, int y0, int a, double fi, double alpha)
{
    float fiRad = fi * (PI / 180.0);
    float alphaRad = alpha * (PI / 180.0);

    sf::Vector2f A(x0, y0);
    
    sf::Vector2f baseVec(a, 0.f);
    sf::Vector2f rotatedBase = rotateV(baseVec, fiRad);
    sf::Vector2f B = addV(A, rotatedBase);

    sf::Vector2f v = subV(B, A);
    sf::Vector2f vPerp = perp90(v);
    sf::Vector2f C = addV(A, vPerp);
    sf::Vector2f D = addV(B, vPerp);

    appendLine(A, B);
    appendLine(C, D);
    appendLine(A, C);
    appendLine(B, D);

    sf::Vector2f half = mulV(v, 0.5f);
    sf::Vector2f rotatedHalf = rotateV(half, -alphaRad);

    sf::Vector2f apex = addV(C, rotatedHalf);

    appendLine(C, apex);
    appendLine(D, apex);

    if (n == 0) return;

    sf::Vector2f v1 = subV(apex, C);
    double len1 = std::sqrt(double(v1.x * v1.x + v1.y * v1.y));
    int a1 = (std::lround(len1));
    double fi1 = std::atan2(double(v1.y), double(v1.x)) * (180.0 / PI);

    sf::Vector2f v2 = subV(D, apex);
    double len2 = std::sqrt(double(v2.x * v2.x + v2.y * v2.y));
    int a2 = (std::lround(len2));
    double fi2 = std::atan2(double(v2.y), double(v2.x)) * (180.0 / PI);

    if (a1 > 0) pifagor(n - 1, std::lround(C.x), std::lround(C.y), a1, fi1, alpha);
    if (a2 > 0) pifagor(n - 1, std::lround(apex.x), std::lround(apex.y), a2, fi2, alpha);

}


int main()
{
    unsigned width = 1920;
    unsigned height = 1080;


    pifagor(10, width / 2, height - 10, 50, 0, 60);

    sf::RenderWindow window(sf::VideoMode({ width, height }), "Pifagor");

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(lines);
        window.display();
    }
}