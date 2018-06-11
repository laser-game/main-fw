#include "player.hpp"
#include "globals.hpp"

Player::Player()
{
    BasicPlayer::live();
}

void Player::death(void)
{
    BasicPlayer::death();
    color.set_rgb(
      global->color_driver->color.get_red(),
      global->color_driver->color.get_green(),
      global->color_driver->color.get_blue()
    );

    global->sound_player->play_dont_give_up();
    global->timer_spirit->start_tim_it();
    global->color_driver->rgb(0, 0, 0);
}

void Player::live(void)
{
    global->timer_spirit->stop_tim_it();
    BasicPlayer::live();
    global->color_driver->rgb(color.get_red(), color.get_green(), color.get_blue());
    global->sound_player->play_keep_going();
}
