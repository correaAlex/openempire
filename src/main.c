#include "Video.h"
#include "Input.h"
#include "Units.h"
#include "Args.h"

int32_t main(int32_t argc, char* argv[])
{
    const Args args = Args_Parse(argc, argv);
    const Video video = Video_Setup(1000, 500, args.demo ? "Render Demo" : "Open Empires");
    const Data data = Data_Load(args.path);
    const Map map = Map_Make(60, data.terrain);
    const Grid grid = Grid_Make(map.cols, map.rows, map.tile_width, map.tile_height);
    Overview overview = Overview_Init(video.xres, video.yres, grid);
    Units units = Units_New(8, map, grid, data.graphics);
    int32_t cycles = 0;
    if(args.demo)
        Video_RenderDataDemo(video, data, args.color);
    else
    for(Input input = Input_Ready(); !input.done; input = Input_Pump(input))
    {
        const Field field = Units_Field(units, map);
        const int32_t t0 = SDL_GetTicks();
        Map_Edit(map, overview, input);
        overview = Overview_Update(overview, input);
        units = Units_Caretake(units, data.graphics, overview, grid, input, map, field);
        Video_Render(video, data, map, units, overview, input, cycles);
        Field_Free(field);
        const int32_t t1 = SDL_GetTicks();
        const int32_t dt = t1 - t0;
        const int32_t ms = 1000 / 60 - dt;
        SDL_Delay(ms < 0 ? 0 : ms);
        cycles++;
        if(args.measure)
            if(cycles > 10) // NOTE: Measure performance with valgrind --tool=cachegrind.
                break;
    }
    Units_Free(units);
    Map_Free(map);
    Data_Free(data);
    Video_Free(video);
}
