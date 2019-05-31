#include "Unit.h"

#include "Rect.h"
#include "Util.h"

Unit Unit_Move(Unit unit, const Grid grid)
{
    if(unit.path.count > 0)
    {
        // Given more than one path index exists, the first index can be skippe as it points to the middle of the first tile.

        if(unit.path.count > 1 && unit.path_index == 0)
            unit.path_index++;

        // The last point index accounts for the grid offset, otherwise, as the last point index is approached, tiles
        // are stepped towards the middle.

        const Point zero = { 0, 0 };
        const Point select = (unit.path_index == unit.path.count - 1) ? unit.cart_grid_offset_goal : zero;
        const Point goal_grid_coords = Grid_GetGridPointWithOffset(grid, unit.path.point[unit.path_index], select);
        const Point unit_grid_coords = Grid_GetGridPointWithOffset(grid, unit.cart, unit.cart_grid_offset);
        const Point delta = Point_Sub(goal_grid_coords, unit_grid_coords);
        if(Point_Mag(delta) < 3) // XXX: Is this too small? What about really fast moving guys?
        {
            unit.path_index++;
            if(unit.path_index == unit.path.count)
                unit.path = Points_Free(unit.path);
            return unit;
        }
        const Point velocity = Point_Normalize(delta, unit.speed);
        unit.cell = Point_Add(unit.cell, velocity);
        unit.cart_grid_offset = Grid_CellToOffset(grid, unit.cell); // XXX. Unit movement is a little shakey. Can somehow integrate?
        unit.cart = Grid_CellToCart(grid, unit.cell);
    }
    return unit;
}

Unit Unit_Make(const Point cart, const Grid grid, const Graphics file)
{
    static Unit zero;
    Unit unit = zero;
    unit.cart = cart;
    unit.cell = Grid_CartToCell(grid, cart);
    unit.file = file;
    unit.speed = Graphics_GetSpeed(file);;
    unit.file_name = Graphics_GetString(file);
    return unit;
}
