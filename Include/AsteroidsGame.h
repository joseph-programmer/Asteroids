#ifndef ASTEROIDSGAME_H
#define ASTEROIDSGAME_H

#include "olcPixelGameEngine.h"
#include <vector>
#include <array>
#include <random>

/**
 * @brief The AsteroidsGame class handles the main logic and rendering for the Asteroids game.
 */
class AsteroidsGame : public olc::PixelGameEngine
{
public:
    /**
     * @brief Constructs the AsteroidsGame object.
     */
    AsteroidsGame();

    /**
     * @brief Called once at the start, used for initialization.
     *
     * @return true if initialization is successful, false otherwise.
     */
    bool OnUserCreate() override;

    /**
     * @brief Called every frame, used for updating game logic and rendering.
     *
     * @param fElapsedTime The time elapsed since the last frame.
     * @return true to continue running the game, false to exit.
     */
    bool OnUserUpdate(float fElapsedTime) override;

private:
    /**
     * @brief Represents the player's spaceship.
     */
    struct Spaceship
    {
        olc::vf2d pos;   /**< The position of the spaceship. */
        olc::vf2d vel;   /**< The velocity of the spaceship. */
        float angle;     /**< The angle the spaceship is facing. */
    } player; /**< The player’s spaceship instance. */

    /**
     * @brief Represents an asteroid in the game.
     */
    struct Asteroid
    {
        olc::vf2d pos;                    /**< The position of the asteroid. */
        olc::vf2d vel;                    /**< The velocity of the asteroid. */
        float angle;                      /**< The angle of rotation of the asteroid. */
        float angleVel;                   /**< The angular velocity of the asteroid. */
        int size;                         /**< The size category of the asteroid. */
        std::vector<olc::vf2d> model;     /**< The vector of points defining the asteroid's shape. */
    };

    /**
     * @brief Represents a bullet fired by the spaceship.
     */
    struct Bullet
    {
        olc::vf2d pos;      /**< The position of the bullet. */
        olc::vf2d vel;      /**< The velocity of the bullet. */
        float lifeTime;     /**< The time the bullet has been active. */
    };

    std::vector<Asteroid> asteroids;  /**< The vector of asteroids currently in the game. */
    std::vector<Bullet> bullets;      /**< The vector of bullets currently in the game. */

    int score;    /**< The player's current score. */
    int lives;    /**< The number of lives the player has left. */
    bool gameOver; /**< Whether the game is over or not. */

    std::vector<olc::vf2d> vecModelShip; /**< The vector of points defining the ship's model. */
    std::mt19937 rng;                    /**< Random number generator used for spawning asteroids. */

    /**
     * @brief Handles the player's input for controlling the spaceship.
     *
     * @param fElapsedTime The time elapsed since the last frame.
     */
    void HandleInput(float fElapsedTime);

    /**
     * @brief Updates the game objects' positions and states.
     *
     * @param fElapsedTime The time elapsed since the last frame.
     */
    void UpdateGameObjects(float fElapsedTime);

    /**
     * @brief Checks for and handles collisions between game objects.
     */
    void CheckCollisions();

    /**
     * @brief Draws all game objects and UI elements to the screen.
     */
    void DrawGame();

    /**
     * @brief Spawns a new asteroid in the game.
     */
    void SpawnAsteroid();

    /**
     * @brief Spawns a new asteroid at a specific position and size.
     *
     * @param pos The position to spawn the asteroid.
     * @param size The size category of the asteroid.
     * @param targetVector The vector to add the new asteroid to.
     */
    void SpawnAsteroid(const olc::vf2d& pos, int size, std::vector<Asteroid>& targetVector);

    /**
     * @brief Wraps the position of game objects around the screen edges.
     *
     * @param pos The position to wrap.
     */
    void WrapCoordinates(olc::vf2d& pos);

    /**
     * @brief Checks if a point is inside a polygon, considering rotation.
     *
     * @param point The point to check.
     * @param polygonPos The position of the polygon.
     * @param polygonModel The vector of points defining the polygon's shape.
     * @param polygonAngle The rotation angle of the polygon.
     * @return true if the point is inside the polygon, false otherwise.
     */
    bool IsCollision(const olc::vf2d& point, const olc::vf2d& polygonPos, const std::vector<olc::vf2d>& polygonModel, float polygonAngle);

    /**
     * @brief Draws a wireframe model on the screen.
     *
     * @param vecModelCoordinates The vector of points defining the model.
     * @param pos The position to draw the model.
     * @param r The rotation angle to apply to the model.
     * @param s The scale to apply to the model.
     * @param col The color to draw the model in.
     */
    void DrawWireframeModel(const std::vector<olc::vf2d>& vecModelCoordinates, const olc::vf2d& pos, float r = 0.0f, float s = 1.0f, olc::Pixel col = olc::WHITE);

    /**
     * @brief Rotates a point around the origin by a specified angle.
     *
     * @param point The point to rotate.
     * @param angle The angle to rotate the point by.
     * @return The rotated point.
     */
    olc::vf2d RotatePoint(const olc::vf2d& point, float angle);
};

#endif // ASTEROIDSGAME_H
