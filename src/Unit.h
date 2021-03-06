#pragma once

#include "Points.h"
#include "Graphics.h"
#include "Trigger.h"
#include "State.h"
#include "Field.h"
#include "Resource.h"
#include "Registrar.h"
#include "Color.h"
#include "Grid.h"
#include "Trait.h"
#include "Direction.h"
#include "Type.h"

typedef struct Unit
{
    struct Unit* interest;
    struct Unit* parent;
    struct Unit* rally;
    Trait trait;
    Point cart;
    Point cart_grid_offset;
    Point cart_goal;
    Point cart_grid_offset_goal;
    Point cell;
    Point cell_last;
    Point cell_interest_inanimate;
    Point velocity;
    Point group_alignment;
    Point stressors;
    Point entropy;
    Points path;
    Color color;
    Direction dir;
    State state;
    Graphics file;
    Trigger trigger;
    int32_t interest_id;
    int32_t parent_id;
    int32_t rally_id;
    int32_t child_lock_id;
    int32_t entropy_static;
    int32_t id;
    int32_t path_index;
    int32_t path_index_timer;
    int32_t command_group;
    int32_t health;
    int32_t state_timer;
    int32_t dir_timer;
    int32_t garbage_collection_timer;
    int32_t grid_flash_timer;
    int32_t attack_frames_per_dir;
    int32_t fall_frames_per_dir;
    int32_t decay_frames_per_dir;
    int32_t expire_frames;
    int32_t child_count;
    uint16_t is_selected_by;
    bool is_engaged_in_melee;
    bool must_garbage_collect;
    bool is_state_locked;
    bool is_already_tiled;
    bool was_wall_pushed;
    bool is_timing_to_collect;
    bool has_children;
    bool is_floating;
    bool is_triggered;
    bool must_skip_debris;
    bool must_repath_with_recover;
    bool using_aggro_move;
    bool is_flash_on;
    bool is_being_built;
    bool has_direct;
    bool has_parent_lock;
}
Unit;

int32_t Unit_GetIdNext(void);

void Unit_SetIdNext(const int32_t id);

int32_t Unit_GetCommandGroupNext(void);

void Unit_SetCommandGroupNext(const int32_t command_group);

void Unit_IncrementCommandGroup(void);

void Unit_UpdatePathIndex(Unit* const, const int32_t index, const bool reset_path_index_timer);

void Unit_FreePath(Unit* const);

void UpdateCart(Unit* const, const Grid);

void Unit_UndoMove(Unit* const, const Grid);

void Unit_Move(Unit* const, const Grid);

void Unit_Lock(Unit* const);

void Unit_Unlock(Unit* const);

void Unit_SetState(Unit* const, const State, const bool reset_state_timer);

Unit Unit_Make(const Point, const Point, const Grid, const Graphics, const Color, const Registrar, const bool at_center, const bool is_floating, const Trigger, const bool is_being_built);

void Unit_Print(Unit* const);

void ApplyStressors(Unit* const);

void Unit_Flow(Unit* const, const Grid);

bool Unit_InPlatoon(Unit* const, Unit* const);

void Unit_SetDir(Unit* const, const Point);

bool Unit_HasDirectPath(Unit* const, const Grid, const Field);

void Unit_MockPath(Unit* const, const Point cart_goal, const Point cart_grid_offset_goal);

void Unit_Flag(Unit* const);

int32_t Unit_GetLastExpireTick(Unit* const);

int32_t Unit_GetLastAttackTick(Unit* const);

int32_t Unit_GetLastDecayTick(Unit* const);

int32_t Unit_GetLastFallTick(Unit* const);

Resource Unit_Melee(Unit* const, const Grid);

Point Unit_Separate(Unit* const, Unit* const);

bool Unit_IsDead(Unit* const);

bool Unit_IsExempt(Unit* const);

Point Unit_GetShift(Unit* const, const Point);

bool Unit_IsDifferent(Unit* const, Unit* const);

bool Unit_HasNoPath(Unit* const);

bool Unit_HasPath(Unit* const);

bool Unit_IsType(Unit* const, const Color, const Type);

void Unit_Preserve(Unit* const, const Unit* const);

void Unit_SetInterest(Unit* const, Unit* const);

void Unit_SetRally(Unit* const, Unit* const);

bool Unit_FlashTimerTick(Unit* const);

Graphics Unit_GetConstructionFile(Unit* const);

void Unit_SetParent(Unit* const, Unit* const);

bool Unit_IsConstruction(Unit* const);

bool Unit_AreEnemies(Unit* const, Unit* const);

void Unit_LayFarm(Unit* const, const Map);

bool Unit_CanAnimateClipAnimate(Unit* const unit, Unit* const other);

bool Unit_IsSelectedByColor(Unit* const, const Color);

void Unit_ClearSelectedColor(Unit* const, const Color);

void Unit_ClearSelectedAllColors(Unit* const);

void Unit_SetSelectedColor(Unit* const, const Color);

bool Unit_IsPointWithinDimensions(Unit* const, const Point);

void Unit_MakeRubble(Unit*, const Grid, const Registrar);

void Unit_UpdateCellInterestInanimate(Unit* const, const Grid);

void Unit_EngageWithMock(Unit* const, Unit* const, const Grid);

void Unit_PreservedUpgrade(Unit* const, const Grid, const Registrar, const Graphics);

bool Unit_IsVillager(Unit* const);
