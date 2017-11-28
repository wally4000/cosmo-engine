//
// Created by efry on 12/11/2017.
//

#include <stdlib.h>
#include "actor_worktype.h"
#include "player.h"
#include "effects.h"
#include "game.h"
#include "dialog.h"
#include "input.h"
#include "sound/sfx.h"
#include "tile.h"
#include "map.h"

void actor_wt_133_boss_purple_15411(ActorData *actor)
{

}

void actor_wt_159_unknown(ActorData *actor)
{

}

void actor_wt_acid(ActorData *actor)
{

}

void actor_wt_alien_eating_space_plant(ActorData *actor)
{

}

void actor_wt_angry_moon(ActorData *actor)
{

}

void actor_wt_big_red_jumper_frozen(ActorData *actor)
{

}

void actor_wt_big_red_plant(ActorData *actor)
{

}

void actor_wt_big_saw_blade(ActorData *actor)
{

}

void actor_wt_big_yellow_spike(ActorData *actor)
{

}

const static uint8 blue_ball_frame_num_tbl[] = {
        2, 2, 2, 0, 3, 3, 3, 0, 0, 2, 2, 0, 0, 1, 1, 0, 1, 3, 3, 3, 0, 1, 1, 0, 1, 1, 1
};

const static uint8 blue_ball_moving_left_frame_num_tbl[] =  {7, 6, 5, 4};
const static uint8 blue_ball_moving_right_frame_num_tbl[] = {4, 5, 6, 7};

void actor_wt_blue_ball(ActorData *actor)
{
    if(actor->falling_counter != 0)
    {
        actor->data_1 = 0;
        actor->data_2 = 0x14;
        if(actor->falling_counter < 2)
        {
            actor->frame_num = 1;
            actor->frame_num = 10;
            return;
        }

        if(actor->falling_counter < 2 || actor->falling_counter > 4)
        {
            actor->y = actor->y - 1;
            display_actor_sprite_maybe(0x56, 9, actor->x, actor->y - 2, 0);
            actor->frame_num = 10;
        }
        else
        {
            display_actor_sprite_maybe(0x56, 8, actor->x, actor->y - 2, 0);
            actor->frame_num = 10;
        }
        return;
    }

    if (actor->data_1 == 0)
    {
        actor->data_2 = actor->data_2 + 1;
        actor->frame_num = blue_ball_frame_num_tbl[actor->data_2];
        if (actor->data_2 == 0x1a)
        {
            actor->data_2 = 0;
            if (actor->y == player_y_pos || (sub_1106F() & 1) == 0)
            {
                if(actor->x < player_x_pos + 1 + 1)
                {
                    if(actor->x + 2 <= player_x_pos)
                    {
                        actor->data_1 = 2;
                        actor->data_2 = 0;
                        actor->frame_num = 3;
                        actor->data_3 = 6;
                    }
                }
                else
                {
                    actor->data_1 = 1;
                    actor->data_2 = 0;
                    actor->frame_num = 2;
                    actor->data_3 = 6;
                }
            }
        }
    }

    if(actor->data_3 != 0)
    {
        actor->data_3 = actor->data_3 - 1;
        return;
    }
    
    if (actor->data_1 == 1)
    {
        actor->x--;
        check_actor_move_left_or_right(actor, LEFT);

        if(actor->has_moved_left_flag != 0)
        {
            actor->frame_num = blue_ball_moving_left_frame_num_tbl[actor->data_2 & 3];
            actor->data_2 = actor->data_2 + 1;
            if(actor->data_2 == 0x10)
            {
                actor->data_1 = 0;
                actor->data_2 = 0;
            }
            return;
        }

        actor->data_1 = 0;
        actor->data_2 = 0;
        actor->frame_num = 0;
        return;
    }
    else
    {
        if (actor->data_1 != 2)
        {
            return;
        }

        actor->x++;
        check_actor_move_left_or_right(actor, RIGHT);
        if (actor->has_moved_right_flag != 0)
        {
            actor->frame_num = blue_ball_moving_right_frame_num_tbl[actor->data_2 & 3];
            actor->data_2 = actor->data_2 + 1;
            if(actor->data_2 == 12)
            {
                actor->data_1 = 0;
                actor->data_2 = 0;
            }
        }
        else
        {
            actor->data_1 = 0;
            actor->data_2 = 0;
            actor->frame_num = 0;
        }
    }

    return;
}

const static sint8 bird_swoop_y_offset_tbl[] = {
        2, 2, 2, 1, 1, 1, 0, 0, 0, -1, -1, -1, -2, -2, -2
};

void actor_wt_blue_bird(ActorData *actor)
{
    if(actor->data_1 == 0)
    {
        if(actor->x + 1 <= player_x_pos)
        {
            if(rand() % 10 != 0)
            {
                actor->data_2 = 4;
            }
            else
            {
                actor->data_2 = 5;
            }
        }
        else
        {
            if(rand() % 10 != 0)
            {
                actor->data_2 = 0;
            }
            else
            {
                actor->data_2 = 1;
            }
        }
        actor->frame_num = actor->data_2;
        actor->data_3 = actor->data_3 + 1;
        if(actor->data_3 == 0x1e)
        {
            actor->data_1 = 1;
            actor->data_3 = 0;
        }
    }
    else
    {
        if(actor->data_1 == 1)
        {
            actor->data_3 = actor->data_3 + 1;
            if(actor->data_3 != 0x14)
            {
                if((actor->data_3 & 1) != 0 && actor->data_3 < 10)
                {
                    actor->y = actor->y - 1;
                }
            }
            else
            {
                actor->data_3 = 0;
                actor->data_1 = 2;
                if(actor->x + 1 <= player_x_pos)
                {
                    actor->data_4 = 1;
                }
                else
                {
                    actor->data_4 = 0;
                }
            }

            if(actor->x + 1 <= player_x_pos)
            {
                actor->frame_num = (actor->data_3 & 1) + 6;
            }
            else
            {
                actor->frame_num = (actor->data_3 & 1) + 2;
            }
        }
        else
        {

            if(actor->data_1 == 2)
            {
                actor->data_3 = actor->data_3 + 1;
                if(actor->data_4 != 0)
                {
                    actor->frame_num = (actor->data_3 & 1) + 6;
                    actor->x = actor->x + 1;
                }
                else
                {
                    actor->frame_num = (actor->data_3 & 1) + 1 + 1;
                    actor->x = actor->x - 1;
                }
                actor->y = actor->y + bird_swoop_y_offset_tbl[actor->data_3 - 1];
                if(actor->data_3 == 15)
                {
                    actor->data_1 = 1;
                    actor->data_3 = 10;
                }
            }
        }
    }
    return;
}

void actor_wt_blue_cube_platform(ActorData *actor)
{

}

void actor_wt_blue_mobile_trampoline_car(ActorData *actor)
{

}

void actor_wt_blue_platform(ActorData *actor)
{

}

void actor_wt_blue_turret_alien(ActorData *actor)
{
    actor->data_2--;
    if(actor->data_2 == 0)
    {
        actor->data_1++;
        actor->data_2 = 3;
        if(actor->data_1 != 3)
        {
            actor->frame_num++;
            switch (actor->frame_num - 2)
            {
                case 0:
                    actor_add_new(0x6d, actor->x - 1, actor->y - 1);
                    break;

                case 3:
                    actor_add_new(0x42, actor->x - 1, actor->y + 1);
                    break;

                case 6:
                    actor_add_new(0x44, actor->x + 1, actor->y + 1);
                    break;

                case 9:
                    actor_add_new(0x43, actor->x + 5, actor->y + 1);
                    break;

                case 12:
                    actor_add_new(0x6e, actor->x + 5, actor->y - 1);
                    break;

                default : break;
            }
        }
    }

    if(actor->data_1 == 0)
    {
        if(actor->y < player_y_pos - 2)
        {
            if(actor->y < player_y_pos - 2)
            {
                if(actor->x - 2 <= player_x_pos)
                {
                    if(actor->x + 3 >= player_x_pos)
                    {
                        if(actor->x - 2 < player_x_pos && actor->x + 3 >= player_x_pos)
                        {
                            actor->frame_num = 6;
                            actor->x = actor->data_3 + 1;
                        }
                    }
                    else
                    {
                        actor->frame_num = 9;
                        actor->x = actor->data_3 + 1;
                    }
                }
                else
                {
                    actor->frame_num = 3;
                    actor->x = actor->data_3;
                }

                if(actor->x - 2 == player_x_pos)
                {
                    actor->frame_num = 6;
                    actor->x = actor->data_3 + 1;
                }
            }
        }
        else
        {
            if(actor->x + 1 <= player_x_pos)
            {
                if(actor->x + 2 <= player_x_pos)
                {
                    actor->frame_num = 12;
                    actor->x = actor->data_3 + 1;
                }
            }
            else
            {
                actor->frame_num = 0;
                actor->x = actor->data_3;
            }
        }
    }

    if(actor->data_1 == 3)
    {
        actor->data_2 = 0x1b;
        actor->data_1 = 0;
    }

    if(actor->frame_num > 14)
    {
        actor->frame_num = 14;
    }

    return;
}

void actor_wt_bomb(ActorData *actor)
{
    if(actor->frame_num == 3)
    {
        actor->data_2 = actor->data_2 + 1;
        actor->data_1 = actor->data_1 + 1;
        if((actor->data_1 & 1) != 0 && actor->frame_num == 3)
        {
            actor_tile_display_func_index = 2;
        }

        if(actor->data_2 == 10)
        {
            actor->is_deactivated_flag_maybe = 1;
            exploding_balls_effect(actor->x - 2, actor->y + 1 + 1);
            actor_tile_display_func_index = 1;

            struct6_add_sprite(actor->x - 2, actor->y);

            if((actor->data_1 & 1) != 0 && actor->frame_num == 3)
            {
                display_actor_sprite_maybe(0x18, actor->frame_num, actor->x, actor->y, 2);
            }
        }
    }
    else
    {
        actor->data_1 = actor->data_1 + 1;
        if(actor->data_1 == 5)
        {
            actor->data_1 = 0;
            actor->frame_num++;
        }
    }

    if(sprite_blocking_check(1, 0x18, 0, actor->x, actor->y) != NOT_BLOCKED)
    {
        actor->y--;
    }
    return;

}

void actor_wt_bonus_bomb(ActorData *actor)
{

}

void actor_wt_bonus_item(ActorData *actor)
{
    if(actor->data_1 != 0)
    {
        actor_tile_display_func_index = 4;
    }

    if (actor->data_4 == 0)
    {
        actor->frame_num = actor->frame_num + 1;
    }
    else
    {
        actor->data_3 = (actor->data_3 ? -1 : 0) + 1;
        if (actor->data_3 != 0)
        {
            actor->frame_num = actor->frame_num + 1;
        }
    }

    if(actor->frame_num == actor->data_5)
    {
        actor->frame_num = 0;
    }

    if(actor->data_5 == 1 && actor->actorInfoIndex != 0xca && actor->data_4 == 0)
    {
        if((rand() & 0x3f) == 0)
        {
            effect_add_sprite(0x17, 8, rand() % actor->data_1 + actor->x, rand() % actor->data_2 + actor->y, 0, 1);
        }
    }

    return;
}

const static uint8  clam_trap_frame_num_tbl[] = {
        0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0
};

void actor_wt_clam_trap(ActorData *actor)
{
    if(actor->data_2 != 0)
    {
        if(actor->data_3 == 1)
        {
            play_sfx(0x28);
        }
        actor->frame_num = clam_trap_frame_num_tbl[actor->data_3];
        actor->data_3++;
        if(actor->data_3 >= 0x18)
        {
            byte_2E17C = 0;
        }
        
        if(actor->data_3 == 0x1b)
        {
            actor->data_3 = 0;
            actor->data_2 = 0;
            byte_2E17C = 0;
        }
        
        if(struct6_1B4FC(actor->actorInfoIndex, actor->frame_num, actor->x, actor->y) != 0)
        {
            player_add_to_score(0xfa);
            
            explode_effect_add_sprite(actor->actorInfoIndex, actor->frame_num, actor->x, actor->y);
            actor->is_deactivated_flag_maybe = 1;
            byte_2E17C = 0;
        }
    }
    else
    {
        if(struct6_1B4FC(actor->actorInfoIndex, actor->frame_num, actor->x, actor->y) != 0)
        {
            player_add_to_score(0xfa);
            
            explode_effect_add_sprite(actor->actorInfoIndex, actor->frame_num, actor->x, actor->y);
            actor->is_deactivated_flag_maybe = 1;
        }
    }
    return;
}

void actor_wt_container(ActorData *actor)
{

}

void actor_wt_crate_bomb_box(ActorData *actor)
{

}

void actor_wt_cyan_spitting_plant(ActorData *actor)
{
    actor->data_4++;
    if(actor->data_4 == 0x32)
    {
        actor->data_4 = 0;
        actor->frame_num = 0;
    }

    if(actor->data_4 == 0x2a)
    {
        actor->frame_num = 1;
    }

    if(actor->data_4 == 0x2d)
    {
        actor->frame_num = 2;
        if(actor->data_5 != 2)
        {
            actor_add_new(0x6e, actor->x + 4, actor->y - 1);
        }
        else
        {
            actor_add_new(0x6d, actor->x - 1, actor->y - 1);
        }
    }
    return;
}

void actor_wt_destructable_pedestal(ActorData *actor)
{

}

void actor_wt_door(ActorData *actor)
{

}

void actor_wt_dragonfly(ActorData *actor)
{

}

void actor_wt_egg_head(ActorData *actor)
{

}

void actor_wt_end_of_level_marker(ActorData *actor)
{
    if(actor->y <= player_y_pos && actor->data_1 == 0)
    {
        finished_level_flag_maybe = 1;
    }
    else
    {
        if(actor->y >= player_y_pos && actor->data_1 != 0)
        {
            finished_game_flag_maybe = 1;
        }
    }

    actor_tile_display_func_index = 1;
    return;
}

void actor_wt_energy_beam(ActorData *actor)
{

}

void actor_wt_extending_arrow(ActorData *actor)
{
    if(actor->data_1 >= 0x1f)
    {
        actor->data_1 = 0;
    }
    else
    {
        actor->data_1 = actor->data_1 + 1;
    }
    
    if(actor->data_1 == 0x1d || actor->data_1 == 0x1a)
    {
        if(is_sprite_on_screen(actor->actorInfoIndex, 0, actor->x, actor->y) != 0)
        {
            play_sfx(9);
        }
    }
    
    if(actor->data_5 == 0)
    {
        if(actor->data_1 > 0x1c)
        {
            actor->x = actor->x + 1;
        }
        else
        {
            if(actor->data_1 > 0x19)
            {
                actor->x = actor->x - 1;
                return;
            }
        }
        return;
    }
    if(actor->data_1 > 0x1c)
    {
        actor->x = actor->x - 1;
        return;
    }
    if(actor->data_1 > 0x19)
    {
        actor->x = actor->x + 1;
        return;
    }
    return;
}

void actor_wt_frozen_duke_nukum(ActorData *actor)
{

}

void actor_wt_ghost(ActorData *actor)
{

}

void actor_wt_green_plant(ActorData *actor)
{
    if(actor->data_2 != 0)
    {
        actor->y = actor->y + 1;
        actor->data_4 = actor->data_4 + 1;
        if(actor->data_4 == 7)
        {
            actor->data_2 = 0;
            actor->data_3 = 0;
            actor->data_1 = 12;
        }
        return;
    }

    if(actor->data_3 < actor->data_1)
    {
        actor->data_3 = actor->data_3 + 1;
        return;
    }

    actor->data_5 = (actor->data_5 ? -1 : 0) + 1;
    actor->frame_num = actor->frame_num + 1;
    if(actor->frame_num == 4)
    {
        actor->frame_num = 0;
    }

    if(actor->data_4 != 0)
    {
        if(actor->data_4 == 7)
        {
            play_sfx(0x35);
        }

        actor->data_4 = actor->data_4 - 1;
        actor->y = actor->y - 1;
    }

    if(struct6_1B4FC(0x91, 0, actor->x, actor->y) != 0)
    {
        actor->data_2 = 1;
    }

    return;
}

void actor_wt_green_pruny_cabbage_ball(ActorData *actor)
{

}

void actor_wt_green_roamer_worm(ActorData *actor)
{

}

const uint8 byte_28EFE[] = { 0, 4, 5, 6, 5, 4};

void actor_wt_hint_dialog(ActorData *actor)
{
    actor->data_4 = (actor->data_4 ? -1 : 0) + 1;
    if(actor->data_4 != 0)
    {
        actor->data_3 = actor->data_3 + 1;
    }

    display_actor_sprite_maybe(0x7d, byte_28EFE[actor->data_3 % 6], actor->x, actor->y - 2, 0);

    actor->data_2 = actor->data_2 + 1;
    if(actor->data_2 == 4)
    {
        actor->data_2 = 1;
    }

    display_actor_sprite_maybe(0x7d, actor->data_2, actor->x, actor->y, 0);
    actor_tile_display_func_index = 1;

    if(player_check_collision_with_actor(0x7d, 0, actor->x, actor->y - 2) != 0)
    {
        word_32EAC = 1;
        if(game_play_mode != 0)
        {
            byte_2E21C = 1;
        }
        if((up_key_pressed != 0 && word_32B88 == 0) || byte_2E21C == 0)
        {
            play_sfx(0x1e);
            ingame_hint_dialogs(actor->data_5);
        }
        byte_2E21C = 1;
    }
    return;
}

void actor_wt_horizontal_flame(ActorData *actor)
{

}

void actor_wt_hoverboard(ActorData *actor)
{
    actor->frame_num = actor->frame_num + 1;
    actor->frame_num = actor->frame_num & 3;
    if(word_32B88 != 0)
    {
        actor->x = player_x_pos;
        actor->y = player_y_pos + 1;
        return;
    }
    
    actor->data_2++;
    if(actor->data_2 % 10 == 0)
    {
        if(sprite_blocking_check(1, 0x72, 0, actor->x, actor->y + 1) != NOT_BLOCKED)
        {
            actor->y = actor->y - 1;
        }
        else
        {
            actor->y = actor->y + 1;
            if(sprite_blocking_check(1, 0x72, 0, actor->x, actor->y + 1) != NOT_BLOCKED)
            {
                actor->y = actor->y - 1;
                return;
            }
        }
        return;
    }
    return;
}

void actor_wt_invisible_exit_marker_right(ActorData *actor)
{
    if(actor->x <= player_x_pos + 3)
    {
        finished_level_flag_maybe = 1;
        return;
    }
    actor_tile_display_func_index = 1;
    return;
}

const static uint8 jaws_and_tongue_frame_num_tbl[] = {2, 3, 4, 3};

void actor_wt_jaws_and_tongue(ActorData *actor)
{
    if(actor->data_1 == 0)
    {
        actor->data_2++;
    }

    if(actor->data_2 == 10)
    {
        actor->data_1 = 1;
        actor->data_2 = 11;
        actor->frame_num = 1;
        actor->data_5 = 1;
        play_sfx(0x26);
    }

    if(actor->frame_num != 0)
    {
        display_actor_sprite_maybe(0x95, jaws_and_tongue_frame_num_tbl[actor->data_3 & 3], actor->x + 6 - actor->data_5, actor->y - 3, 0);
        actor->data_3++;
    }

    if(is_sprite_on_screen(0x95, 1, actor->x, actor->y) == 0)
    {
        
        actor->frame_num = 0;
        actor->data_2 = 0;
        actor->data_1 = 0;
        actor->data_5 = 0;
    }
    actor_tile_display_func_index = 1;
    
    display_actor_sprite_maybe(actor->actorInfoIndex, 1, actor->x, actor->y, 0);
    
    if(actor->data_5 != 0 && actor->data_5 < 4)
    {
        actor->data_5++;
        return;
    }

    display_actor_sprite_maybe(actor->actorInfoIndex, 0, actor->x, actor->y - 1 - actor->data_5, 0);
    return;
}

void actor_wt_jumping_bullet_head(ActorData *actor)
{

}

void actor_wt_mini_ghost(ActorData *actor)
{
    if(actor->data_4 != 0)
    {
        actor->data_4--;
        return;
    }
    
    if(actor->data_1 == 0)
    {
        if(sprite_blocking_check(1, 0x41, 0, actor->x, actor->y + 1) != NOT_BLOCKED)
        {
            actor->can_fall_down_flag = 0;
            actor->data_1 = 1;
            actor->data_4 = 3;
            actor->data_2 = 4;
            actor->frame_num = 1;
            actor->data_3 = 1;
            if(is_sprite_on_screen(0x41, 0, actor->x, actor->y) != 0)
            {
                play_sfx(0x3b);
            }
            return;
        }
        
        if(actor->data_5 != 0)
        {
            actor->data_5--;
        }
        else
        {
            actor->frame_num = 1;
            if(actor->data_3 == 0)
            {
                actor->data_4++;
                return;
            }
        }
    }
    else
    {
        
        if(actor->data_1 == 1)
        {
            actor->y = actor->y - 1;
            actor->frame_num = 0;
            if(actor->data_2 == 4)
            {
                if(is_sprite_on_screen(0x41, 0, actor->x, actor->y) != 0)
                {
                    play_sfx(0x3a);
                }
            }
            
            actor->data_2--;
            if(actor->data_2 == 0)
            {
                actor->data_1 = 0;
                actor->data_5 = 3;
                actor->can_fall_down_flag = 1;
            }
        }
    }
    return;
}

void actor_wt_pink_eye_plant(ActorData *actor)
{
    actor_tile_display_func_index = actor->data_5;
    actor->data_2 = rand() % 0x28;
    if(actor->data_2 <= 0x25)
    {
        actor->data_2 = 0;
    }
    else
    {
        actor->data_2 = 3;
    }

    if(actor->x - 2 > player_x_pos)
    {
        actor->frame_num = actor->data_2;
        return;
    }

    if(actor->x + 1 >= player_x_pos)
    {
        actor->frame_num = actor->data_2 + 1;
    }
    else
    {
        actor->frame_num = actor->data_2 + 2;
    }

    return;
}

void actor_wt_pink_slug(ActorData *actor)
{
    if(actor->data_5 == 0)
    {
        actor->data_4 = (actor->data_4 ? -1 : 0) + 1;
        if(actor->data_4 != 0)
        {
            return;
        }
    }
    if(rand() % 0x28 > 0x25)
    {

        if(actor->data_3 == 0 && actor->data_2 == 0)
        {
            actor->data_3 = 4;
        }
    }

    if(actor->data_3 != 0)
    {
        actor->data_3--;
        if(actor->data_3 == 2)
        {
            if(actor->data_1 == 0)
            {
                actor->frame_num = 2;
                return;
            }

            if(actor->data_2 == 0)
            {
                actor->frame_num = 5;
            }
            return;
        }

        if(actor->data_1 != 0)
        {
            actor->frame_num = 3;
        }
        else
        {
            actor->frame_num = 0;
        }
        return;
    }

    if(actor->data_1 == 0)
    {
        actor->frame_num = (actor->frame_num ? -1 : 0) + 1;
        if(actor->frame_num != 0)
        {
            actor->x--;
            check_actor_move_left_or_right(actor, 2);

            if(actor->has_moved_left_flag == 0)
            {
                actor->data_1 = 1;
            }
        }
        return;
    }

    actor->data_2 = (actor->data_2 ? -1 : 0) + 1;
    if(actor->data_2 == 0)
    {
        actor->x = actor->x + 1;
        actor->frame_num = 1;
        check_actor_move_left_or_right(actor, 3);

        if(actor->has_moved_right_flag == 0)
        {
            actor->data_1 = 0;
        }
        return;
    }

    actor->frame_num = actor->data_2 + 3;
    return;
}

void actor_wt_pipe_transit_direction(ActorData *actor)
{
    actor_tile_display_func_index = 1;
}

void actor_wt_plasma_energy_blue_sprite(ActorData *actor)
{

}

void actor_wt_plasma_fireball(ActorData *actor)
{
    if(actor->data_1 == 0x1d)
    {
        play_sfx(0x24);
    }
    
    if(actor->data_1 >= 0x1e)
    {
        
        if(actor->data_5 != 0)
        {
            
            actor->x = actor->x + 1;
            
            actor->has_moved_right_flag = (sprite_blocking_check(3, actor->actorInfoIndex, 0, actor->x, actor->y) != NOT_BLOCKED ? -1 : 0) + 1;
            if(actor->has_moved_right_flag == 0)
            {
                actor->data_1 = 0;
                effect_add_sprite(0x61, 6, actor->x - 2, actor->y, 1, 1);
                
                actor->x = actor->data_2;
                actor->y = actor->data_3;
                play_sfx(0x1b);
            }
        }
        else
        {
            actor->x = actor->x - 1;
            
            actor->has_moved_left_flag = (sprite_blocking_check(2, actor->actorInfoIndex, 0, actor->x, actor->y) != NOT_BLOCKED ? -1 : 0) + 1;
            if(actor->has_moved_left_flag == 0)
            {
                actor->data_1 = 0;
                effect_add_sprite(0x61, 6, actor->x + 1, actor->y, 1, 1);
                
                actor->x = actor->data_2;
                actor->y = actor->data_3;
                play_sfx(0x1b);
            }
        }
    }
    else
    {
        actor->data_1++;
    }

    if(is_sprite_on_screen(actor->actorInfoIndex, actor->frame_num, actor->x, actor->y) == 0)
    {
        
        actor->data_1 = 0;
        actor->x = actor->data_2;
        actor->y = actor->data_3;
        return;
    }

    actor->frame_num = (actor->frame_num ? -1 : 0) + 1;
    return;
}

void actor_wt_pneumatic_pipe(ActorData *actor)
{
    if(actor->data_2 != 0)
    {
        actor->data_1++;
        actor->data_3++;
        if((actor->data_3 & 1) == 0)
        {
            actor->frame_num = 0;
        }
        else
        {
            actor->frame_num = 4;
        }
        
        if(actor->data_1 == 4)
        {
            actor->data_1 = 1;
        }
        
        display_actor_sprite_maybe(0x69, actor->data_1, actor->x, actor->y + 3, 0);
        return;
    }
    return;
}

void actor_wt_projectile_flashing_ball(ActorData *actor)
{
    if(is_sprite_on_screen(0x44, 0, actor->x, actor->y) == 0)
    {
        actor->is_deactivated_flag_maybe = 1;
        return;
    }

    if(actor->data_1 == 0)
    {
        actor->data_1 = 1;
        play_sfx(0x1a);
    }

    actor->frame_num = (actor->frame_num ? -1 : 0) + 1;

    switch (actor->data_5)
    {
        case 0:
            actor->x = actor->x - 1;
            break;

        case 1:
            actor->x = actor->x - 1;
            actor->y = actor->y + 1;
            break;

        case 2:
            actor->y = actor->y + 1;
            break;

        case 3:
            actor->x = actor->x + 1;
            actor->y = actor->y + 1;
            break;

        case 4:
            actor->x = actor->x + 1;
            break;

        default : break;
    }
}

void actor_wt_question_mark_block(ActorData *actor)
{
    if(word_2E17E != 0)
    {
        actor->data_1 = 1;
        actor->update_while_off_screen_flag = 1;
    }
    
    if(actor->data_1 == 0)
    {
        return;
    }
    if((actor->data_1 & 1) != 0)
    {
        map_write_tile_cell(0x3df8, actor->x, actor->y - 1);
        
        map_write_tile_cell(0x3e00, actor->x + 1, actor->y - 1);
        
        map_write_tile_cell(0x3e08, actor->x, actor->y);
        
        map_write_tile_cell(0x3e10, actor->x + 1, actor->y);
    }
    
    if(sprite_blocking_check(0, actor->actorInfoIndex, 0, actor->x, actor->y - 1) != NOT_BLOCKED)
    {
        
        if((actor->data_1 & 1) == 0)
        {
            map_write_tile_cell(0x3e08, actor->x, actor->y - 1);
            map_write_tile_cell(0x3e10, actor->x + 1, actor->y - 1);
        }
        actor->is_deactivated_flag_maybe = 1;
        return;
    }
    
    if((actor->data_1 & 1) == 0)
    {
        effect_add_sprite(15, 4, actor->x - 1, actor->y - 1, 0, 1);
        return;
    }
    
    actor->data_1++;
    actor->y--;

    return;
}

void actor_wt_red_blue_plant(ActorData *actor)
{
    actor_tile_display_func_index = actor->data_5;
    if(actor->data_2 == 1)
    {
        actor->frame_num = actor->frame_num + 1;
        if(actor->frame_num == 1)
        {
            play_sfx(0x3f);
        }
        
        if(actor->frame_num == 4)
        {
            actor->data_2 = 2;
        }
        return;
    }
    
    if(actor->data_2 == 2)
    {
        actor->frame_num = actor->frame_num - 1;
        if(actor->frame_num == 1)
        {
            actor->data_2 = 0;
            actor->data_1 = 1;
        }
        return;
    }
    
    if(actor->data_1 >= 0x10)
    {
        actor->data_1 = 0;
    }
    else
    {
        actor->data_1++;
    }
    
    if(actor->data_1 != 0)
    {
        actor->frame_num = 0;
    }
    else
    {
        actor->data_2 = 1;
    }
    return;
}

const uint8 word_28EE6[] = { 8, 9, 10, 10, 9, 8};
const uint8 word_28EF2[] = { 10, 9, 8, 8, 9, 10};

void actor_wt_red_chomper_alien(ActorData *actor)
{
    actor->data_4 = (actor->data_4 ? -1 : 0) + 1;

    if(sub_1106F() % 0x5f != 0)
    {
        if(sub_1106F() % 0x64 == 0)
        {
            actor->data_5 = 11;
        }
    }
    else
    {
        actor->data_5 = 10;
    }

    if(actor->data_5 < 11 && actor->data_5 != 0)
    {
        actor->data_5--;
        if(actor->data_5 <= 8)
        {

            if(actor->data_5 != 8)
            {

                actor->data_2 = (actor->data_2 ? -1 : 0) + 1;

                actor->frame_num = actor->data_2 + 6;
            }
            else
            {
                actor->frame_num = 5;
            }
        }
        else
        {
            actor->frame_num = 6;
        }
        if(actor->data_5 != 0)
        {
            return;
        }

        if((sub_1106F() & 1) == 0)
        {
            return;
        }

        if(actor->x < player_x_pos)
        {
            actor->data_1 = 1;
        }
        else
        {
            actor->data_1 = 0;
        }
    }
    else
    {

        if(actor->data_5 > 10)
        {
            if(actor->data_1 != 0)
            {
                actor->frame_num = word_28EF2[actor->data_5 - 11];
            }
            else
            {
                actor->frame_num = word_28EE6[actor->data_5 - 11];
            }

            actor->data_5++;
            if(actor->data_5 == 0x11)
            {
                actor->data_5 = 0;
            }
            return;
        }

        if(actor->data_1 == 0)
        {
            if(actor->data_4 != 0)
            {
                actor->frame_num = (actor->frame_num ? -1 : 0) + 1;
                actor->x = actor->x - 1;
                check_actor_move_left_or_right(actor, LEFT);

                if(actor->has_moved_left_flag == 0)
                {
                    actor->data_1 = 1;
                    actor->frame_num = 4;
                }
            }
            return;
        }

        if(actor->data_4 != 0)
        {
            actor->data_3 = (actor->data_3 ? -1 : 0) + 1;
            actor->frame_num = actor->data_3 + 2;
            actor->x++;
            check_actor_move_left_or_right(actor, RIGHT);

            if(actor->has_moved_right_flag == 0)
            {
                actor->data_1 = 0;
                actor->frame_num = 4;
            }
        }
    }
    return;
}

void actor_wt_retracting_spikes(ActorData *actor)
{
    actor->data_2++;
    if(actor->data_2 == 0x14)
    {
        actor->data_2 = 0;
    }
    
    if(actor->frame_num != 0 || actor->data_2 != 0)
    {
        
        if(actor->frame_num != 2 || actor->data_2 != 0)
        {
            
            if(actor->data_1 == 0)
            {
                
                if(actor->frame_num < 2)
                {
                    actor->frame_num = actor->frame_num + 1;
                }
            }
            else
            {
                if(actor->frame_num > 0)
                {
                    actor->frame_num = actor->frame_num - 1;
                }
            }
        }
        else
        {
            actor->data_1 = 1;
            play_sfx(9);
            actor_tile_display_func_index = 1;
        }
    }
    else
    {
        actor->data_1 = 0;
        play_sfx(9);
    }
    if(actor->frame_num == 2)
    {
        actor_tile_display_func_index = 1;
        return;
    }
    return;
}

void actor_wt_robot_with_blue_arc(ActorData *actor)
{

}

void actor_wt_robotic_spike_ceiling(ActorData *actor)
{
    actor->data_3 = (actor->data_3 ? -1 : 0) + 1;
    if(actor->data_3 == 0)
    {
        return;
    }
    if(actor->data_4 != 0)
    {
        actor->data_4--;
        return;
    }
    
    if(actor->data_2 == 1)
    {
        if(sprite_blocking_check(3, 0x50, 0, actor->x + 1, actor->y) != 0)
        {
            actor->data_4 = 4;
            actor->data_2 = 0;
        }
        else
        {
            if(sprite_blocking_check(3, 0x50, 0, actor->x + 1, actor->y - 1) != 0)
            {
                actor->x = actor->x + 1;
            }
            else
            {
                actor->data_4 = 4;
                actor->data_2 = 0;
            }
        }
        return;
    }
    
    if(sprite_blocking_check(2, 0x50, 0, actor->x - 1, actor->y) != 0)
    {
        actor->data_4 = 4;
        actor->data_2 = 1;
    }
    else
    {
        if(sprite_blocking_check(2, 0x50, 0, actor->x - 1, actor->y - 1) != 0)
        {
            actor->x = actor->x - 1;
        }
        else
        {
            actor->data_4 = 4;
            actor->data_2 = 1;
        }
    }
    
    actor->frame_num = (actor->frame_num ? -1 : 0) + 1;
    return;
}

void actor_wt_robotic_spike_ground(ActorData *actor)
{

}

void actor_wt_rocket(ActorData *actor)
{
    if(actor->data_1 != 0)
    {
        actor->data_1--;
        if(actor->data_1 >= 0x1e)
        {
            return;
        }
        if((actor->data_1 & 1) == 0)
        {

            effect_add_sprite(0x61, 6, actor->x + 1, actor->y + 1, 2, 1);
        }
        else
        {
            effect_add_sprite(0x61, 6, actor->x - 1, actor->y + 1, 8, 1);
        }
        return;
    }

    if(actor->data_2 != 0)
    {
        if(actor->data_2 > 7)
        {
            effect_add_sprite(0x61, 6, actor->x - 1, actor->y + 1, 7, 1);

            effect_add_sprite(0x61, 6, actor->x + 1, actor->y + 1, 3, 1);
            play_sfx(0x31);
        }

        if(actor->data_2 > 1)
        {
            actor->data_2--;
        }

        if(actor->data_2 < 10)
        {
            if(sprite_blocking_check(0, 0xbc, 0, actor->x, actor->y - 1) != 0)
            {
                actor->data_5 = 1;
            }
            else
            {
                actor->y = actor->y - 1;
            }

            if(is_sprite_on_screen(actor->actorInfoIndex, 0, actor->x, actor->y) != 0)
            {
                play_sfx(0x31);
            }
        }

        if(actor->data_2 < 5)
        {
            if(sprite_blocking_check(0, 0xbc, 0, actor->x, actor->y - 1) != 0)
            {
                actor->data_5 = 1;
            }
            else
            {
                actor->y = actor->y - 1;
            }

            actor->data_4 = (actor->data_4 ? -1 : 0) + 1;
            display_actor_sprite_maybe(0xbc, actor->data_4 + 4, actor->x, actor->y + 6, 0);

            if(player_check_collision_with_actor(0xbc, 4, actor->x, actor->y + 6) != 0)
            {
                player_decrease_health();
            }

            if(actor->data_4 != 0)
            {
                effect_add_sprite(0x61, 6, actor->x, actor->y + 6, 5, 1);
            }
        }

        if(actor->x == player_x_pos)
        {
            if(actor->y - 7 <= player_y_pos)
            {
                if(actor->y - 4 >= player_y_pos)
                {
                    player_bounce_height_counter = 0x10;
                    player_bounce_flag_maybe = 1;
                    sub_11062();
                    word_2E1DE = 0;
                    if(actor->y - 7 == player_y_pos)
                    {
                        player_y_pos = player_y_pos + 1;
                    }
                    if(actor->y - 6 == player_y_pos)
                    {
                        player_y_pos = player_y_pos + 1;
                    }
                    if(actor->y - 4 == player_y_pos)
                    {
                        player_y_pos = player_y_pos - 1;
                    }
                }
            }
        }

        if(actor->data_2 > 4 && (actor->data_2 & 1) != 0)
        {
            effect_add_sprite(0x61, 6, actor->x, actor->y + 1 + 1, 5, 1);
        }
    }

    if(actor->data_5 != 0)
    {
        actor->is_deactivated_flag_maybe = 1;
        explode_effect_add_sprite(0xbc, 1, actor->x, actor->y);

        explode_effect_add_sprite(0xbc, 2, actor->x + 1, actor->y);

        explode_effect_add_sprite(0xbc, 3, actor->x + 1 + 1, actor->y);

        struct6_add_sprite(actor->x - 4, actor->y);

        struct6_add_sprite(actor->x + 1, actor->y);
        actor_tile_display_func_index = 2;
    }
    return;
}

void actor_wt_rubber_wall(ActorData *actor)
{

}

void actor_wt_satellite(ActorData *actor)
{

}

void actor_wt_security_robot(ActorData *actor)
{

}

void actor_wt_short_dialog(ActorData *actor)
{

}

void actor_wt_silver_robot(ActorData *actor)
{

}

void actor_wt_small_flame(ActorData *actor)
{
    actor->frame_num = actor->frame_num + 1;
    if(actor->frame_num == 6)
    {
        actor->frame_num = 0;
    }
    return;
}

void actor_wt_small_red_plant(ActorData *actor)
{

}

void actor_wt_smoke_rising(ActorData *actor)
{

}

void actor_wt_spark(ActorData *actor)
{

}

void actor_wt_spear_vertical(ActorData *actor)
{
    if(actor->data_1 >= 0x1e)
    {
        actor->data_1 = 0;
    }
    else
    {
        actor->data_1++;
    }
    
    if(actor->data_1 > 0x16)
    {
        actor->y = actor->y - 1;
        return;
    }
    
    if(actor->data_1 > 14)
    {
        actor->y = actor->y + 1;
        return;
    }
    return;
}

void actor_wt_spring(ActorData *actor)
{
    if(actor->data_1 <= 0)
    {
        actor->frame_num = 0;
    }
    else
    {
        actor->frame_num = 1;
        actor->data_1--;
    }

    if(actor->data_5 != 0)
    {
        actor_tile_display_func_index = 4;
        if(actor->frame_num != 0)
        {
            actor->y = actor->data_4;
        }
        else
        {
            actor->y = actor->data_3;
        }
    }
    return;
}

void actor_wt_stone_head(ActorData *actor)
{
    actor->data_4 = (actor->data_4 ? -1 : 0) + 1;
    if(actor->data_1 == 0)
    {
        if(actor->y < player_y_pos)
        {
            if(actor->x <= player_x_pos + 6)
            {
                if(actor->x + 7 > player_x_pos)
                {
                    actor->data_1 = 1;
                    actor->data_2 = actor->y;
                    actor->frame_num = 1;
                    return;
                }
            }
        }
        actor->frame_num = 0;
        return;
    }
    
    if(actor->data_1 == 1)
    {
        actor->frame_num = 1;
        actor->y = actor->y + 1;
        if(sprite_blocking_check(1, 0x2f, 0, actor->x, actor->y) != 0)
        {
            actor->data_1 = 2;
            if(is_sprite_on_screen(0x2f, 0, actor->x, actor->y) != 0)
            {
                play_sfx(0x25);
                
                effect_add_sprite(0x61, 6, actor->x + 1, actor->y, 2, 1);
                effect_add_sprite(0x61, 6, actor->x, actor->y, 8, 1);
                actor->y = actor->y - 1;
            }
            else
            {
                actor->y = actor->y - 1;
            }
            return;
        }
        
        actor->y = actor->y + 1;
        if(sprite_blocking_check(1, 0x2f, 0, actor->x, actor->y) != NOT_BLOCKED)
        {
            actor->data_1 = 2;
            play_sfx(0x25);
            
            effect_add_sprite(0x61, 6, actor->x + 1, actor->y, 2, 1);
            
            effect_add_sprite(0x61, 6, actor->x, actor->y, 8, 1);
            actor->y = actor->y - 1;
            return;
        }
    }
    else
    {
        
        if(actor->data_1 == 2)
        {
            actor->frame_num = 0;
            if(actor->y == actor->data_2)
            {
                actor->data_1 = 0;
            }
            else if(actor->data_4 != 0)
            {
                actor->y = actor->y - 1;
            }
        }
    }
    return;
}

void actor_wt_suction_cup_alien_enemy(ActorData *actor)
{

}

void actor_wt_switch(ActorData *actor)
{

}

void actor_wt_switch_multi_use(ActorData *actor)
{

}

void actor_wt_teleporter(ActorData *actor)
{
    actor_tile_display_func_index = 1;
    if(teleporter_counter == 0 || (rand() & 1) == 0)
    {
        
        display_actor_sprite_maybe(0x6b, 0, actor->x, actor->y, 0);
    }
    else
    {
        
        display_actor_sprite_maybe(0x6b, 0, actor->x, actor->y, 2);
    }
    if((sub_1106F() & 1) != 0)
    {
        display_actor_sprite_maybe(0x6b, (rand() & 1) + 1, actor->x, actor->y, 0);
    }
    if(teleporter_counter == 15)
    {
        effect_add_sprite(15, 4, player_x_pos - 1, player_y_pos, 0, 1);
        effect_add_sprite(15, 4, player_x_pos + 1, player_y_pos, 0, 1);
        effect_add_sprite(15, 4, player_x_pos - 1, player_y_pos - 3, 0, 2);
        effect_add_sprite(15, 4, player_x_pos, player_y_pos - 2, 0, 3);
        effect_add_sprite(15, 4, player_x_pos + 1, player_y_pos - 3, 0, 3);
        play_sfx(0x17);
    }
    if(teleporter_counter > 1)
    {
        teleporter_counter = teleporter_counter - 1;
        return;
    }
    if(teleporter_state_maybe == 3)
    {
        finished_level_flag_maybe = 1;
        return;
    }
    if(teleporter_state_maybe == 0)
    {
        return;
    }
    
    if(actor->data_5 == teleporter_state_maybe || actor->data_5 == 3)
    {
        return;
    }
    player_x_pos = actor->x + 1;
    player_y_pos = actor->y;
    if(player_x_pos - 14 >= 0)
    {
        if(player_x_pos - 14 <= map_width_in_tiles - 38)
        {
            mapwindow_x_offset = player_x_pos - 14;
        }
        else
        {
            mapwindow_x_offset = map_width_in_tiles - 38;
        }
    }
    else
    {
        mapwindow_x_offset = 0;
    }
    if(player_y_pos - 12 >= 0)
    {
        if(player_y_pos - 12 <= map_max_y_offset)
        {
            mapwindow_y_offset = player_y_pos - 12;
        }
        else
        {
            mapwindow_y_offset = map_max_y_offset;
        }
    }
    else
    {
        mapwindow_y_offset = 0;
    }
    teleporter_state_maybe = 0;
    teleporter_counter = 0;
    player_bounce_flag_maybe = 0;
    if(word_2E23C == 0)
    {
        word_2E23C = 1;
        actor_add_new(0xf4, player_x_pos - 1, player_y_pos - 5);
    }
    return;
}

void actor_wt_two_tons(ActorData *actor)
{
    if(actor->data_1 < 0x14)
    {
        actor->data_1++;
    }
    
    if(actor->data_1 == 0x13)
    {
        actor->data_2 = 1;
    }
    
    if(actor->data_2 == 1)
    {
        if(actor->frame_num >= 3)
        {
            
            actor->data_2 = 2;
            if(is_sprite_on_screen(0x2d, 4, actor->x - 1, actor->y + 3) != 0)
            {
                play_sfx(0x25);
            }
        }
        else
        {
            actor->frame_num = actor->frame_num + 1;
            if(actor->frame_num == 1)
            {
                actor->data_3 = 1;
            }
            else
            {
                if(actor->frame_num == 2)
                {
                    actor->data_3 = 2;
                }
                else
                {
                    if(actor->frame_num == 3)
                    {
                        actor->data_3 = 4;
                    }
                }
            }
            
            actor->y = actor->y + actor->data_3;
        }
    }
    
    if(actor->data_2 == 2)
    {
        if(actor->frame_num <= 0)
        {
            
            actor->data_2 = 0;
            actor->data_1 = 0;
            actor->data_3 = 0;
        }
        else
        {
            actor->frame_num--;
            if(actor->frame_num == 0)
            {
                actor->data_3 = 1;
            }
            else
            {
                if(actor->frame_num == 1)
                {
                    actor->data_3 = 2;
                }
                else
                {
                    if(actor->frame_num == 2)
                    {
                        actor->data_3 = 4;
                    }
                }
            }
            
            actor->y = actor->y - actor->data_3;
        }
    }
    
    if(player_check_collision_with_actor(0x2d, 4, actor->x - 1, actor->y + 3) != 0)
    {
        player_decrease_health();
        return;
    }
    
    display_actor_sprite_maybe(0x2d, 4, actor->x - 1, actor->y + 3, 0);
    return;
}

const sint8 score_effect_x_tbl[] = {
        -2, -1, 0, 1, 2, 2, 1, 0, -1, -2
};
void actor_wt_floating_score_effect(ActorData *actor)
{
    actor_tile_display_func_index = 1;
    actor->data_1++;
    actor->frame_num = (actor->frame_num ? -1 : 0) + 1;
    if(actor->data_1 > 0x1f)
    {
        actor->y = actor->y - 1;
        actor->x = actor->x + score_effect_x_tbl[(actor->data_1 - 32) % 10];
    }

    if(actor->data_1 < 4)
    {
        actor->y = actor->y - 1;
    }

    if(actor->data_1 == 0x64 || is_sprite_on_screen(actor->actorInfoIndex, actor->frame_num, actor->x, actor->y) == 0)
    {
        actor->is_deactivated_flag_maybe = 1;
        actor_tile_display_func_index = 1;
    }

    display_actor_sprite_maybe(actor->actorInfoIndex, actor->frame_num, actor->x, actor->y, 5);
    return;
}

void actor_wt_speech_bubble(ActorData *actor)
{
    actor_tile_display_func_index = 1;
    if(actor->data_1 == 0)
    {
        play_sfx(0x39);
        if(actor->actorInfoIndex == 0xf6)
        {
            player_add_to_score(0xc350);
        }
    }

    actor->data_1++;
    if(actor->data_1 != 0x14)
    {
        display_actor_sprite_maybe(actor->actorInfoIndex, 0, player_x_pos - 1, player_y_pos - 5, 5);
    }
    else
    {
        actor->is_deactivated_flag_maybe = 1;
    }

    return;
}

void actor_wt_unknown_232(ActorData *actor)
{

}

void check_actor_move_left_or_right(ActorData *actor, Direction direction_of_movement)
{
    uint16 sprite_width = actor_get_tile_info(actor->actorInfoIndex, actor->frame_num)->width;

    if(direction_of_movement == LEFT)
    {
        BlockingType block_status = sprite_blocking_check(2, actor->actorInfoIndex, actor->frame_num, actor->x, actor->y);

        actor->has_moved_left_flag = (block_status != NOT_BLOCKED ? -1 : 0) + 1;
        if(actor->has_moved_left_flag == 0 && block_status != SLOPE)
        {
            actor->x = actor->x + 1;
            return;
        }
        if(block_status != SLOPE)
        {
            if(sprite_blocking_check(1, actor->actorInfoIndex, actor->frame_num, actor->x, actor->y + 1) == 0)
            {
                uint8 tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x + sprite_width, actor->y + 1) / 8];
                if((tile_attr & TILE_ATTR_SLOPED) != 0)
                {

                    tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x + sprite_width - 1, actor->y + 1 + 1) / 8];
                    if((tile_attr & TILE_ATTR_SLOPED) != 0)
                    {

                        tile_attr = tileattr_mni_data[ map_get_tile_cell(actor->x + sprite_width - 1, actor->y + 1) / 8];
                        if((tile_attr & TILE_ATTR_BLOCK_DOWN) != 0)
                        {
                            return;
                        }

                        actor->has_moved_left_flag = 1;

                        if((tile_attr & TILE_ATTR_SLOPED) == 0)
                        {
                            actor->y = actor->y + 1;
                        }
                        return;
                    }
                }
                if(actor->has_moved_left_flag == 0)
                {
                    actor->x = actor->x + 1;
                    return;
                }

                if(actor->non_blocking_flag_maybe != 0 || sprite_blocking_check(2, actor->actorInfoIndex, actor->frame_num, actor->x, actor->y + 1) != 0)
                {
                    return;
                }

                tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x + sprite_width - 1, actor->y + 1)/ 8];
                if((tile_attr & TILE_ATTR_SLOPED) == 0)
                {
                    actor->x = actor->x + 1;
                    actor->has_moved_left_flag = 0;
                }
            }
            else
            {
                actor->has_moved_left_flag = 1;
            }
        }
        else
        {
            actor->has_moved_left_flag = 1;
            actor->y = actor->y - 1;
        }
    }
    else
    {
        BlockingType block_status = sprite_blocking_check(3, actor->actorInfoIndex, actor->frame_num, actor->x, actor->y);

        actor->has_moved_right_flag = (block_status != NOT_BLOCKED ? -1 : 0) + 1;
        if(actor->has_moved_right_flag == 0 && block_status != SLOPE)
        {
            actor->x = actor->x - 1;
            return;
        }
        if(block_status != SLOPE)
        {
            if(sprite_blocking_check(1, actor->actorInfoIndex, actor->frame_num, actor->x, actor->y + 1))
            {
                uint8 tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x - 1, actor->y + 1) /8];
                if((tile_attr & TILE_ATTR_SLOPED) != 0)
                {

                    tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x, actor->y + 1 + 1) / 8];
                    if((tile_attr & TILE_ATTR_SLOPED) != 0)
                    {

                        tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x, actor->y + 1) / 8];
                        if((tile_attr & TILE_ATTR_BLOCK_DOWN) != 0)
                        {
                            return;
                        }

                        actor->has_moved_right_flag = 1;
                        tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x, actor->y + 1) / 8];
                        if((tile_attr & TILE_ATTR_SLOPED) == 0)
                        {
                            actor->y = actor->y + 1;
                            return;
                        }
                        return;
                    }
                }
                if(actor->has_moved_right_flag == 0)
                {
                    actor->x = actor->x - 1;
                    return;
                }

                if(actor->non_blocking_flag_maybe == 0 && sprite_blocking_check(3, actor->actorInfoIndex, actor->frame_num, actor->x, actor->y + 1) == 0)
                {

                    tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x, actor->y + 1) / 8];
                    if((tile_attr & TILE_ATTR_SLOPED) == 0)
                    {

                        actor->x = actor->x - 1;
                        actor->has_moved_right_flag = 0;
                        return;
                    }
                    return;
                }
            }
            else
            {
                actor->has_moved_right_flag = 1;
            }
        }
        else
        {
            actor->has_moved_right_flag = 1;
            actor->y = actor->y - 1;
        }
    }

    return;
}
