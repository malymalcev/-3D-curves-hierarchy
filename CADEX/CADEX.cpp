#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "Curve.h"

using namespace std;

bool pairCircles(const shared_ptr<Circle>& a, const shared_ptr<Circle>& b) {
    return a->getRadius() < b->getRadius();
};


int main()
{
    // Задание 2. Заполняем вектор случайными кривыми со случайными параметрами.
    vector<shared_ptr<Curve>> curves;
    srand(time(0));
    int type = 0;
    Point center;
    double radius_a, radius_b, step;
    for (int i = 0; i < 10; i++)
    {
        type = rand() % 3;
        cout << type << endl;
        // Не совсем понял, должны быть центры кривых в начале координат или нет, поэтому сделал 
        // для случая с любой начальной точкой, но если центр должен быть { 0,0,0 }, то раскомментируйте 
        //строку 29 и закомментируйте 30.
        //center = { 0,0,0 };
        center = { (double)(rand()) / (double)(rand()),(double)(rand()) / (double)(rand()),(double)(rand()) / (double)(rand()) };
        radius_a = rand() % 10;
        radius_b = rand() % 10;
        step = rand() % 10;

        //Вариант с вещественными радиусами и шагом.
        //center = { (double)(rand()) / (double)(rand()),(double)(rand()) / (double)(rand()),(double)(rand()) / (double)(rand()) };
        //radius_a = (double)(rand()) / (double)(rand());
        //radius_b = (double)(rand()) / (double)(rand());
        //step = (double)(rand()) / (double)(rand());

        if (type == 0) {
            shared_ptr<Circle> circle = shared_ptr<Circle>(new Circle(radius_a, center));
            curves.push_back(circle);
        }
        else if (type == 1)
        {
            curves.push_back(shared_ptr<Ellipse>(new Ellipse(radius_a, radius_b, center)));
        }
        else
        {
            curves.push_back(shared_ptr<Helix>(new Helix(radius_a, center, step)));
        }
    }



    // Задание 3. Выводим значения точек и производных для кривых из вектора curves при t = PI / 4
    cout<<"Coordinates of points and derivatives:"<< endl;
    double t = M_PI / 4;
    for (const auto& curve : curves)
    {
        Point p = curve->getPoint(t);
        Vector v = curve->getVector(t);
        cout.precision(8);
        cout <<"Point: " << p.x << ", " << p.y << ", " << p.z <<"; Derivative:" << v.dx << ", " << v.dy << ", " << v.dz << endl;
    }

    // Задание 4. Создаем вектор circles и заполняем его окружностями, которые есть в векторе curves.
    vector<shared_ptr<Circle>> circles;
    for (auto& curve : curves) {
        if ( auto circle = dynamic_pointer_cast<Circle>(curve)) {
            circles.push_back(circle);
        }
    }

    // Задание 5-6. Сортируем вектор circles в порядке возрастания радиусов окружностей и одновременно с этим суммируем их.
    double sumRadius = 0.0;
    double tmp = 0.0;
    sort(circles.begin(), circles.end(), pairCircles);
    cout << "\nSorted Circles by Radius:" << endl;
    for ( auto& circle : circles) {
        tmp = circle->getRadius();
        sumRadius += tmp;
        cout << "Circle with radius: " << tmp << endl;
    }
    cout << "Sum of radii:" << sumRadius << endl;
}
