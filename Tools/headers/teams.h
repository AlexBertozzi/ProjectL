typedef enum {

    TEAM_ENEMY_PRJECTILE = -2,
    TEAM_ENEMY = -1,
    //must be last of enemy team

    //all non player or enemy goes in the middle
    TEAM_TERRAIN = 0,
    TEAM_DECORATION = 1, //usually no collisions

    //must be first of allied team
    TEAM_PLAYER = 2,
    TEAM_PLAYER_PROJECTILE = 3
};