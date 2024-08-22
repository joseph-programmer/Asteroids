#include "AsteroidsGame.h"

AsteroidsGame::AsteroidsGame()
{
    sAppName = "Asteroids";
    score = 0;
    lives = 3;
    gameOver = false;
}

bool AsteroidsGame::OnUserCreate()
{
    rng.seed(std::random_device()());

    // Initialize game objects
    player = { {ScreenWidth() / 2.0f, ScreenHeight() / 2.0f}, {0, 0}, 0 };

    // Define ship model
    vecModelShip = {
        {0, -5.5f},
        {-2.5f, 2.5f},
        {2.5f, 2.5f}
    };

    // Spawn initial asteroids
    for (int i = 0; i < 4; i++)
    {
        SpawnAsteroid();
    }

    return true;
}

bool AsteroidsGame::OnUserUpdate(float fElapsedTime)
{
    if (!gameOver)
    {
        HandleInput(fElapsedTime);
        UpdateGameObjects(fElapsedTime);
        CheckCollisions();
        WrapCoordinates(player.pos);
    }

    DrawGame();
    return true;
}

void AsteroidsGame::HandleInput(float fElapsedTime)
{
    if (GetKey(olc::Key::LEFT).bHeld) player.angle -= 5.0f * fElapsedTime;
    if (GetKey(olc::Key::RIGHT).bHeld) player.angle += 5.0f * fElapsedTime;

    if (GetKey(olc::Key::UP).bHeld)
    {
        player.vel += olc::vf2d(sin(player.angle), -cos(player.angle)) * 20.0f * fElapsedTime;
    }

    if (GetKey(olc::Key::SPACE).bPressed)
    {
        bullets.push_back({ player.pos,
            olc::vf2d(200.0f * sinf(player.angle), -200.0f * cosf(player.angle)),
            0.0f });
    }
}

void AsteroidsGame::UpdateGameObjects(float fElapsedTime)
{
    player.pos += player.vel * fElapsedTime;

    for (auto& a : asteroids)
    {
        a.pos += a.vel * fElapsedTime;
        a.angle += a.angleVel * fElapsedTime;
        WrapCoordinates(a.pos);
    }

    for (auto& b : bullets)
    {
        b.pos += b.vel * fElapsedTime;
        b.lifeTime += fElapsedTime;
        WrapCoordinates(b.pos);
    }

    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const Bullet& b) { return b.lifeTime > 2.0f; }),
        bullets.end());
}

void AsteroidsGame::CheckCollisions()
{
    std::vector<Asteroid> newAsteroids;

    // Check bullet-asteroid collisions
    for (auto bullet_it = bullets.begin(); bullet_it != bullets.end(); )
    {
        bool bullet_destroyed = false;

        for (auto asteroid_it = asteroids.begin(); asteroid_it != asteroids.end(); )
        {
            if (IsCollision(bullet_it->pos, asteroid_it->pos, asteroid_it->model, asteroid_it->angle))
            {
                score += 100 * (3 - asteroid_it->size);

                // Spawn new asteroids
                if (asteroid_it->size > 0 && asteroids.size() + newAsteroids.size() < 20)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        SpawnAsteroid(asteroid_it->pos, asteroid_it->size - 1, newAsteroids);
                    }
                }

                asteroid_it = asteroids.erase(asteroid_it);
                bullet_destroyed = true;
                break;
            }
            else
            {
                ++asteroid_it;
            }
        }

        if (bullet_destroyed)
        {
            bullet_it = bullets.erase(bullet_it);
        }
        else
        {
            ++bullet_it;
        }
    }

    // Add new asteroids after iteration
    asteroids.insert(asteroids.end(), newAsteroids.begin(), newAsteroids.end());

    // Check player-asteroid collisions
    for (const auto& a : asteroids)
    {
        if (IsCollision(player.pos, a.pos, a.model, a.angle))
        {
            lives--;
            if (lives <= 0)
            {
                gameOver = true;
            }
            else
            {
                player.pos = { ScreenWidth() / 2.0f, ScreenHeight() / 2.0f };
                player.vel = { 0, 0 };
            }
            break;
        }
    }
}

void AsteroidsGame::DrawGame()
{
    Clear(olc::BLACK);

    DrawWireframeModel(vecModelShip, player.pos, player.angle, 1.0f, olc::WHITE);

    for (const auto& a : asteroids)
    {
        DrawWireframeModel(a.model, a.pos, a.angle, 1.0f, olc::WHITE);
    }

    for (const auto& b : bullets)
    {
        Draw(b.pos, olc::YELLOW);
    }

    DrawString(10, 10, "SCORE: " + std::to_string(score), olc::WHITE);
    DrawString(10, 20, "LIVES: " + std::to_string(lives), olc::WHITE);

    if (gameOver)
    {
        DrawString(ScreenWidth() / 2 - 40, ScreenHeight() / 2, "GAME OVER", olc::WHITE);
    }
}

void AsteroidsGame::SpawnAsteroid()
{
    SpawnAsteroid({ float(rand() % ScreenWidth()), float(rand() % ScreenHeight()) }, 2, asteroids);
}

void AsteroidsGame::SpawnAsteroid(const olc::vf2d& pos, int size, std::vector<Asteroid>& targetVector)
{
    Asteroid newAsteroid;
    newAsteroid.pos = pos;
    newAsteroid.size = size;
    float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f * 3.14159f;
    newAsteroid.vel = olc::vf2d(cosf(angle), sinf(angle)) * (30.0f + size * 5.0f);
    newAsteroid.angle = 0.0f;
    newAsteroid.angleVel = static_cast<float>(rand() % 100) / 100.0f - 0.5f;

    // Generate asteroid model
    int numPoints = 8 + size * 2;
    float radius = 10.0f + size * 5.0f;
    std::uniform_real_distribution<float> radiusDist(radius * 0.8f, radius * 1.2f);

    for (int i = 0; i < numPoints; i++)
    {
        float theta = (float)i / numPoints * 2.0f * 3.14159f;
        float r = radiusDist(rng);
        newAsteroid.model.push_back({ r * cosf(theta), r * sinf(theta) });
    }

    targetVector.push_back(newAsteroid);
}

void AsteroidsGame::WrapCoordinates(olc::vf2d& pos)
{
    if (pos.x < 0) pos.x = ScreenWidth();
    if (pos.x > ScreenWidth()) pos.x = 0;
    if (pos.y < 0) pos.y = ScreenHeight();
    if (pos.y > ScreenHeight()) pos.y = 0;
}

bool AsteroidsGame::IsCollision(const olc::vf2d& point, const olc::vf2d& polygonPos, const std::vector<olc::vf2d>& polygonModel, float polygonAngle)
{
    // Transform point to polygon's local space
    olc::vf2d localPoint = RotatePoint(point - polygonPos, -polygonAngle);

    int count = polygonModel.size();
    bool inside = false;

    for (int i = 0, j = count - 1; i < count; j = i++)
    {
        if (((polygonModel[i].y > localPoint.y) != (polygonModel[j].y > localPoint.y)) &&
            (localPoint.x < (polygonModel[j].x - polygonModel[i].x) * (localPoint.y - polygonModel[i].y) /
                (polygonModel[j].y - polygonModel[i].y) + polygonModel[i].x))
        {
            inside = !inside;
        }
    }

    return inside;
}

void AsteroidsGame::DrawWireframeModel(const std::vector<olc::vf2d>& vecModelCoordinates, const olc::vf2d& pos, float r, float s, olc::Pixel col)
{
    std::vector<olc::vf2d> vecTransformedCoordinates;
    int verts = vecModelCoordinates.size();
    vecTransformedCoordinates.resize(verts);

    for (int i = 0; i < verts; i++)
    {
        vecTransformedCoordinates[i] = RotatePoint(vecModelCoordinates[i], r) * s + pos;
    }

    for (int i = 0; i < verts + 1; i++)
    {
        int j = (i + 1);
        DrawLine(vecTransformedCoordinates[i % verts], vecTransformedCoordinates[j % verts], col);
    }
}

// Helper function to rotate a point around the origin
olc::vf2d AsteroidsGame::RotatePoint(const olc::vf2d& point, float angle)
{
    float cs = cos(angle), sn = sin(angle);
    return { point.x * cs - point.y * sn, point.x * sn + point.y * cs };
}
