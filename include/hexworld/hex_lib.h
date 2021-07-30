#pragma once

struct Hexagon {
    int64_t X;
    int64_t Y;
    int64_t Z;
    std::string Type;
    std::string Direction;

    Hexagon(int x_, int y_, int z_, std::string type_, std::string direction_)
            :X(x_), Y(y_), Z(z_), Type(type_), Direction(direction_) {};
};

struct AxialCoordinates {
    int32_t Q;
    int32_t R;

    AxialCoordinates(int32_t Q_, int32_t R_) {
        Q = Q_;
        R = R_;
    }
};