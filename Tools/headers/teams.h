#pragma once

enum Team{

    TEAM_ENEMY_PRJECTILE,
    //must be last of enemy team
    TEAM_ENEMY,

    //all non player or enemy goes in the middle
    TEAM_TERRAIN,
    TEAM_DECORATION, //usually no collisions

    //must be first of allied team
    TEAM_PLAYER,
    TEAM_PLAYER_PROJECTILE
};