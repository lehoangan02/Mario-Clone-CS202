#include "Level.hpp"
LevelFactory& LevelFactory::GetLevelFactory()
{
    static LevelFactory Factory;
    return Factory;
}
Level* LevelFactory::CreateLevel(int Type, Mediator* mediator)
{
    Level* level = nullptr;
    switch (Type)
    {
    case LEVEL_101:
        level = Level101::GetLevel101();
        level->setMediator(mediator);
        return level;
        break;
    case LEVEL_TESTING:
        level = LevelTesting::GetLevelTesting();
        level->setMediator(mediator);
        return level;
        break;
    case LEVEL_102:
        level = Level102::GetLevel102();
        level->setMediator(mediator);
        return level;
        break;
    case LEVEL_103:
        level = Level103::GetLevel103();
        level->setMediator(mediator);
        return level;
        break;
    case HIDDEN_LEVEL_101:
        level = HiddenLevel101::GetHiddenLevel101();
        level->setMediator(mediator);
        return level;
        break;
    case HIDDEN_LEVEL_103:
        level = HiddenLevel103::GetHiddenLevel103();
        level->setMediator(mediator);
        return level;
        break;
    case HIDDEN_LEVEL_102:
        level = HiddenLevel102::GetHiddenLevel102();
        level->setMediator(mediator);
        return level;
        break;
    case HIDDEN_LEVEL_112:
        break;
    default:
        return nullptr;
        break;

    }
    return level;
}
Level::Level()
{
    m_CameraPosition = { 0, 0 };
    m_Ground = Ground::GetGround();
    m_EnemyHandler.setLevel(this);
    m_FireballHandler.setLevel(this);
}
Level::~Level()
{
    for (auto& object : m_Environment)
    {
        delete object;
    }
    for (auto& object : m_EnvironmentInteractive)
    {
        delete object.first;
        delete object.second;
    }
    for (auto& object : m_Drawables)
    {
        delete object;
    }
    for (auto& object : m_Lifts)
    {
        delete object;
    }
    for (auto& object : m_EndPipes)
    {
        delete object;
    }
    // for (auto& object : m_Enemies)
    // {
    //     delete object;
    // }
    for (auto& object : m_IdleCoin)
    {
        delete object;
    }

}
void Level::attachPlayer(Character* Player)
{
    if (Player == nullptr) {
        std::cerr << "Error: Trying to attach a nullptr as Player!" << std::endl;
        return;
    }
    m_Player = Player;
    m_Player->setPosition(m_StartPosition);
    m_EndPipeHandler.attachPlayer(Player);
}
void Level::checkEnvironmentCollisions()
{
}
void Level::resolveEnvironmentCollisions()
{
    if (m_Player->isDead()) return;
    if (m_InSpecialPipe) return;
    for (int i = 0; i < m_Environment.size(); i++)
    {
        AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
        AABBox EnvironmentBox = AABBox(m_Environment[i]->m_Position, m_Environment[i]->getSize());
        EnvironmentBox.setFixed(true);
        if (isColliding(PlayerBox, EnvironmentBox))
        {
            if (isCollidingVertically(PlayerBox, EnvironmentBox))
            {
                if (isCollidingOnBottom(PlayerBox, EnvironmentBox))
                {
                    if (m_LevelID == LevelFactory::LEVEL_103)
                    {
                        m_Player->resetVelocity();
                    }
                    else if (!isCollidingHorizontallyRawLess(PlayerBox, EnvironmentBox, 15.0f))
                    {
                        m_Player->resetVelocity();
                    }
                    if (m_Environment[i]->getType() == EnvironmentObjectFactory::EnvironmentObjectType::BRICK)
                    {
                        SoundManager::getInstance().PlaySoundEffect(HITBLOCK_SOUND);
                    }
                }
                else if (isCollidingOnTop(PlayerBox, EnvironmentBox))
                {

                    if (!isCollidingHorizontallyRawLess(PlayerBox, EnvironmentBox, 15.0f) && m_LevelID != LevelFactory::LEVEL_103)
                    {

                        m_Player->resetVelocity();
                        m_Player->onPlatform();
                    }
                    else if (m_LevelID == LevelFactory::LEVEL_103)
                    {
                        std::cout << "Resetting Velocity 103" << std::endl;
                        m_Player->resetVelocity();
                        m_Player->onPlatform();
                    }
                    
                }

            }

            resolveCollisions(PlayerBox, EnvironmentBox);
            m_Player->setPosition(PlayerBox.getPosition());
            m_Environment[i]->m_Position = EnvironmentBox.getPosition();
        }
    }
    for (int i = 0; i < m_Lifts.size(); i++)
    {
        AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
        AABBox EnvironmentBox = AABBox(m_Lifts[i]->m_Position, m_Lifts[i]->getSize());
        EnvironmentBox.setFixed(true);
        if (isColliding(PlayerBox, EnvironmentBox))
        {
            if (isCollidingVertically(PlayerBox, EnvironmentBox))
            {
                m_Player->resetVelocity();
                if (isCollidingOnTop(PlayerBox, EnvironmentBox))
                {
                    m_Player->onPlatform();
                }
            }
            resolveCollisions(PlayerBox, EnvironmentBox);
            m_Player->setPosition(PlayerBox.getPosition());
            m_Lifts[i]->m_Position = EnvironmentBox.getPosition();
        }
    }
}
void Level::resolveInteractiveEnvironmentCollisions()
{
    for (int i = 0; i < m_EnvironmentInteractive.size(); i++)
    {
        AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
        AABBox EnvironmentBox = AABBox(m_EnvironmentInteractive[i].first->m_Position, m_EnvironmentInteractive[i].first->getSize());
        EnvironmentBox.setFixed(true);
        if (isColliding(PlayerBox, EnvironmentBox))
        {
            if (isCollidingVertically(PlayerBox, EnvironmentBox) && !(isCollidingHorizontallyRawLess(PlayerBox, EnvironmentBox, 15.0f)))
            {
                if (isCollidingOnTop(PlayerBox, EnvironmentBox))
                {
                    m_Player->onPlatform();
                }
                else if (isCollidingOnBottom(PlayerBox, EnvironmentBox))
                {
                    Item* CurrentItem = m_EnvironmentInteractive[i].second;
                    if (CurrentItem)
                    {
                        CurrentItem->onNotify();
                        if (!(m_EnvironmentInteractive[i].first->isHit()))
                        {
                            if (CurrentItem->getItemID() == Itemtype::MUSHROOM)
                            {
                                if (!(m_EnvironmentInteractive[i].second->isHit()))
                                {
                                    std::cout << "Mushroom" << std::endl;
                                    if (m_EnvironmentInteractive[i].first->isHit())
                                    {
                                        std::cout << "Hitted" << std::endl;
                                    }
                                    else
                                    {
                                        SoundManager::getInstance().PlaySoundEffect(ITEMPOPUP_SOUND);
                                    }
                                }
                            }
                            else if (CurrentItem->getItemID() == Itemtype::COIN)
                            {

                                if (!(m_EnvironmentInteractive[i].second->isHit()))
                                {
                                    std::cout << "Coin" << std::endl;
                                    if (m_EnvironmentInteractive[i].first->isHit())
                                    {
                                        std::cout << "Hitted" << std::endl;
                                    }
                                    else
                                    {
                                        SoundManager::getInstance().PlaySoundEffect(COIN_SOUND);
                                        m_Player->increaseScore();
                                        
                                    }
                                }
                            }
                            else if (CurrentItem->getItemID() == Itemtype::FIREFLOWER)
                            {
                                std::cout << "FireFlower" << std::endl;
                            }
                        }
                        m_EnvironmentInteractive[i].first->onNotify();
                    }
                }
            }
            if (!(m_EnvironmentInteractive[i].first->getObjectID() == EnvironmentInteractiveObjectFactory::EnvironmentInteractiveObjectType::BREAKABLE_BRICK))
            {
                if (isCollidingVertically(PlayerBox, EnvironmentBox) && !(isCollidingHorizontallyRawLess(PlayerBox, EnvironmentBox, 15.0f)))
                {
                    m_Player->resetVelocity();
                }
                resolveCollisions(PlayerBox, EnvironmentBox);
                m_Player->setPosition(PlayerBox.getPosition());
                m_EnvironmentInteractive[i].first->m_Position = EnvironmentBox.getPosition();
                // std::cout << "Resolving Collisions" << std::endl;
                // std::cout << "Not Breakable Brick" << std::endl;
                // std::cout << "Interactive Item Type: " << m_EnvironmentInteractive[i].first->getType() << std::endl;
            }
            else
            {
                if (!(m_Player->isSuper()))
                {
                    if (!(m_EnvironmentInteractive[i].first->isHit()))
                    {
                        if (isCollidingVertically(PlayerBox, EnvironmentBox) && !(isCollidingHorizontallyRawLess(PlayerBox, EnvironmentBox, 15.0f)))
                        {
                            m_Player->resetVelocity();
                        }
                        resolveCollisions(PlayerBox, EnvironmentBox);
                        m_Player->setPosition(PlayerBox.getPosition());
                        m_EnvironmentInteractive[i].first->m_Position = EnvironmentBox.getPosition();
                    }
                }
                else
                {
                    BreakableBrick* BreakBrick = dynamic_cast<BreakableBrick*>(m_EnvironmentInteractive[i].first);
                    if (!(BreakBrick->m_BreakAnimation.isFinished()))
                    {
                        if (isCollidingVertically(PlayerBox, EnvironmentBox) && !(isCollidingHorizontallyRawLess(PlayerBox, EnvironmentBox, 15.0f)))
                        {
                            std::cout << "Not Finished" << std::endl;
                            m_Player->resetVelocity();
                            m_EnvironmentInteractive[i].first->onNotify();
                        }
                        resolveCollisions(PlayerBox, EnvironmentBox);
                        m_Player->setPosition(PlayerBox.getPosition());
                        m_EnvironmentInteractive[i].first->m_Position = EnvironmentBox.getPosition();
                    }
                }
            }
        }
    }
}
void Level::applyBoundaries()
{
    if (m_Player->isDead()) return;
    // std::cout << "Applying Boundaries" << std::endl;
    if (isPlayerInHole())
    {
        // std::cout << "In Hole" << std::endl;
    }
    else if (m_Player->GetPosition().y > m_Ground->m_Position.y - m_Player->GetSize().y)
    {
        // std::cout << "On Ground" << std::endl;
        m_Player->setPosition(Vector2{ m_Player->GetPosition().x, m_Ground->m_Position.y - m_Player->GetSize().y });
        m_Player->resetVelocity();
        m_Player->onPlatform();
    }
}
void Level::handleItemLogic()
{
    for (int i = 0; i < m_EnvironmentInteractive.size(); i++)
    {
        Item* CurrentItem = m_EnvironmentInteractive[i].second;
        if (!CurrentItem) continue;
        if (CurrentItem->getItemID() == Itemtype::MUSHROOM)
        {
            AABBox ItemBox = AABBox(CurrentItem->GetPosition(), CurrentItem->GetSize());
            if (m_Ground->isInHole(ItemBox)) continue;
            Mushroom* MushroomItem = dynamic_cast<Mushroom*>(CurrentItem);
            // std::cout << "Mushroom position: " << MushroomItem->GetPosition().y << std::endl;
            if (MushroomItem->GetPosition().y > m_Ground->m_Position.y - MushroomItem->GetSize().y)
            {
                // std::cout << "Mushroom is on the ground" << std::endl;
                MushroomItem->setPosition(MushroomItem->GetPosition().x, m_Ground->m_Position.y - MushroomItem->GetSize().y);
                MushroomItem->ResetYVelocity();
            }
        }
        else if (CurrentItem->getItemID() == Itemtype::STARMAN)
        {
            AABBox ItemBox = AABBox(CurrentItem->GetPosition(), CurrentItem->GetSize());
            if (m_Ground->isInHole(ItemBox)) continue;
            StarMan* StarManItem = dynamic_cast<StarMan*>(CurrentItem);
            if (StarManItem->GetPosition().y > m_Ground->m_Position.y - StarManItem->GetSize().y)
            {
                StarManItem->setPosition(StarManItem->GetPosition().x, m_Ground->m_Position.y - StarManItem->GetSize().y);
                StarManItem->FlipDirectionY();
            }
        }
    }
    for (int i = 0; i < m_EnvironmentInteractive.size(); i++)
    {
        Item* CurrentItem = m_EnvironmentInteractive[i].second;
        if (!CurrentItem) continue;
        if (CurrentItem->getItemID() == Itemtype::MUSHROOM)
        {
            Mushroom* MushroomItem = dynamic_cast<Mushroom*>(CurrentItem);
            // if (IsKeyPressed(KEY_F))
            // {
            //     std::cout << "Trying to flip" << std::endl;
            //     MushroomItem->FlipDirection();
            // }

            if (MushroomItem->isFinishSpawning())
            {
                MushroomItem->Accelerate(GetFrameTime());
            }
            if (!(MushroomItem->isHit()) && !MushroomItem->isFinishSpawning()) continue;
            for (int j = 0; j < m_EnvironmentInteractive.size(); ++j)
            {
                AABBox ItemBox = AABBox(MushroomItem->GetPosition(), MushroomItem->GetSize());
                AABBox EnvironmentBox = AABBox(m_EnvironmentInteractive[j].first->m_Position, m_EnvironmentInteractive[j].first->getSize());
                EnvironmentBox.setFixed(true);
                if (isCollidingVertically(ItemBox, EnvironmentBox) && !(isCollidingHorizontallyRawLess(ItemBox, EnvironmentBox, 10.0f)))
                {
                    if (isCollidingOnBottom(ItemBox, EnvironmentBox))
                    {
                        MushroomItem->ResetYVelocity();
                    }
                    else if (isCollidingOnTop(ItemBox, EnvironmentBox))
                    {
                        MushroomItem->ResetYVelocity();
                    }
                }
                else if (isCollidingHorizontally(ItemBox, EnvironmentBox))
                {
                    MushroomItem->FlipDirection();
                }
                resolveCollisions(ItemBox, EnvironmentBox);
                MushroomItem->setPosition(ItemBox.getPosition().x, ItemBox.getPosition().y);
                // m_EnvironmentInteractive[i].first->m_Position = EnvironmentBox.getPosition();
            }
        }
        else if (CurrentItem->getItemID() == Itemtype::STARMAN)
        {
            StarMan* StarManItem = dynamic_cast<StarMan*>(CurrentItem);
            if (StarManItem->isFinishedSpawning())
            {
                StarManItem->setFalling();
                StarManItem->Accelerate(GetFrameTime());
            }
            if (!(StarManItem->isHit()) && !StarManItem->isFinishedSpawning()) continue;
            for (int j = 0; j < m_EnvironmentInteractive.size(); ++j)
            {
                AABBox ItemBox = AABBox(StarManItem->GetPosition(), StarManItem->GetSize());
                AABBox EnvironmentBox = AABBox(m_EnvironmentInteractive[j].first->m_Position, m_EnvironmentInteractive[j].first->getSize());
                EnvironmentBox.setFixed(true);
                if (isCollidingVertically(ItemBox, EnvironmentBox) && !(isCollidingHorizontallyRawLess(ItemBox, EnvironmentBox, 10.0f)))
                {
                    if (isCollidingOnBottom(ItemBox, EnvironmentBox))
                    {
                        StarManItem->FlipDirectionY();
                        std::cout << "Flipping Y" << std::endl;
                    }
                    else if (isCollidingOnTop(ItemBox, EnvironmentBox))
                    {
                        StarManItem->FlipDirectionY();
                        std::cout << "Flipping Y" << std::endl;
                    }
                }
                else if (isCollidingHorizontally(ItemBox, EnvironmentBox))
                {
                    StarManItem->FlipDirectionX();
                    std::cout << "Flipping X" << std::endl;
                }
                resolveCollisions(ItemBox, EnvironmentBox);
                StarManItem->setPosition(ItemBox.getPosition().x, ItemBox.getPosition().y);
                // m_EnvironmentInteractive[i].first->m_Position = EnvironmentBox.getPosition();
            }
        }
    }
    for (int i = 0; i < m_EnvironmentInteractive.size(); i++)
    {
        Item* CurrentItem = m_EnvironmentInteractive[i].second;
        if (!CurrentItem) continue;
        if (CurrentItem->getItemID() == Itemtype::MUSHROOM)
        {
            Mushroom* MushroomItem = dynamic_cast<Mushroom*>(CurrentItem);
            if (IsKeyPressed(KEY_F))
            {
                std::cout << "Trying to flip" << std::endl;
                MushroomItem->FlipDirection();
            }
            if (MushroomItem->isFinishSpawning())
            {
                MushroomItem->Accelerate(GetFrameTime());
            }
            else
            {
                continue;
            }
            for (int j = 0; j < m_Environment.size(); j++)
            {
                // std::cout << "j: " << j << std::endl;
                AABBox ItemBox = AABBox(MushroomItem->GetPosition(), MushroomItem->GetSize());
                AABBox EnvironmentBox = AABBox(m_Environment[j]->m_Position, m_Environment[j]->getSize());
                EnvironmentBox.setFixed(true);
                if (isCollidingVertically(ItemBox, EnvironmentBox) && !(isCollidingHorizontallyRawLess(ItemBox, EnvironmentBox, 10.0f)))
                {
                    if (isCollidingOnBottom(ItemBox, EnvironmentBox))
                    {
                        MushroomItem->ResetYVelocity();
                    }
                    else if (isCollidingOnTop(ItemBox, EnvironmentBox))
                    {
                        MushroomItem->ResetYVelocity();
                    }
                }
                else if (isCollidingHorizontally(ItemBox, EnvironmentBox))
                {
                    MushroomItem->FlipDirection();
                }
                resolveCollisions(ItemBox, EnvironmentBox);
                MushroomItem->setPosition(ItemBox.getPosition().x, ItemBox.getPosition().y);
                m_Environment[j]->m_Position = EnvironmentBox.getPosition();
            }

        }
        else if (CurrentItem->getItemID() == Itemtype::STARMAN)
        {
            StarMan* StarManItem = dynamic_cast<StarMan*>(CurrentItem);
            if (StarManItem->isFinishedSpawning())
            {
                StarManItem->setFalling();
                StarManItem->Accelerate(GetFrameTime());
            }
            else
            {
                continue;
            }
            for (int j = 0; j < m_Environment.size(); j++)
            {
                AABBox ItemBox = AABBox(StarManItem->GetPosition(), StarManItem->GetSize());
                AABBox EnvironmentBox = AABBox(m_Environment[j]->m_Position, m_Environment[j]->getSize());
                EnvironmentBox.setFixed(true);
                if (isCollidingVertically(ItemBox, EnvironmentBox) && !(isCollidingHorizontallyRawLess(ItemBox, EnvironmentBox, 10.0f)))
                {
                    if (isCollidingOnBottom(ItemBox, EnvironmentBox))
                    {
                        StarManItem->FlipDirectionY();
                        std::cout << "Flipping Y" << std::endl;
                    }
                    else if (isCollidingOnTop(ItemBox, EnvironmentBox))
                    {
                        StarManItem->FlipDirectionY();
                        std::cout << "Flipping Y" << std::endl;
                    }
                }
                else if (isCollidingHorizontally(ItemBox, EnvironmentBox))
                {
                    StarManItem->FlipDirectionX();
                    std::cout << "Flipping X" << std::endl;
                }
                resolveCollisions(ItemBox, EnvironmentBox);
                StarManItem->setPosition(ItemBox.getPosition().x, ItemBox.getPosition().y);
                m_Environment[j]->m_Position = EnvironmentBox.getPosition();
            }
        }
    }
    for (int i = 0; i < m_EnvironmentInteractive.size(); ++i)
    {
        Item* CurrentItem = m_EnvironmentInteractive[i].second;
        if (!CurrentItem) continue;
        if (CurrentItem->getItemID() == Itemtype::MUSHROOM)
        {
            Mushroom* MushroomItem = dynamic_cast<Mushroom*>(CurrentItem);
            if (MushroomItem->isHit()) continue;
            AABBox ItemBox = AABBox(MushroomItem->GetPosition(), MushroomItem->GetSize());
            AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
            if (isColliding(ItemBox, PlayerBox))
            {
                m_Player->powerUp();
                m_Player->increaseScore(200);
                SoundManager::getInstance().PlaySoundEffect(POWERUP_SOUND);
                MushroomItem->setHit();
            }
        }
        else if (CurrentItem->getItemID() == Itemtype::FIREFLOWER)
        {
            FireFlower* FireFlowerItem = dynamic_cast<FireFlower*>(CurrentItem);
            if (FireFlowerItem->isHit()) continue;
            AABBox ItemBox = AABBox(FireFlowerItem->GetPosition(), FireFlowerItem->GetSize());
            AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
            if (isColliding(ItemBox, PlayerBox))
            {
                m_Player->increLives();
                m_Player->increaseScore(300);
                SoundManager::getInstance().PlaySoundEffect(POWERUP_SOUND);
                FireFlowerItem->setHit();
            }
        }
        else if (CurrentItem->getItemID() == Itemtype::STARMAN)
        {
            StarMan* StarManItem = dynamic_cast<StarMan*>(CurrentItem);
            if (StarManItem->isHit()) continue;
            AABBox ItemBox = AABBox(StarManItem->GetPosition(), StarManItem->GetSize());
            AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
            if (isColliding(ItemBox, PlayerBox))
            {
                m_Player->invincile();
                m_Player->increaseScore(1000);
                MusicManager::getInstance().PlayMusic(Invincible);
                StarManItem->setHit();
            }
        }
    }
    for (auto& object : m_IdleCoin)
    {
        if (object->isHit()) continue;
        object->Update(GetFrameTime());
        AABBox ItemBox = AABBox(object->getPosition(), object->getSize());
        AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
        if (isColliding(ItemBox, PlayerBox) && !object->isHit())
        {
            object->setHit();
            SoundManager::getInstance().PlaySoundEffect(COIN_SOUND);
            m_Player->increaseScore();
        }
    }
}
void Level::render()
{
    float Offset = 900;
    switch (m_Ground->m_WorldType)
    {
    case Level::WorldType::OVERWORLD:
    {
        ClearBackground(Color{ 105, 147, 245, 255 });
        break;
    }
    case Level::WorldType::UNDERGROUND:
    {
        ClearBackground(BLACK);
        break;
    }
    }

    Camera2D camera = { 0 };
    Vector2 target = m_CameraPosition;
    target.x = roundf(target.x);
    target.y = roundf(target.y);
    camera.target = target;

    float CurrentHeight = GetScreenHeight();
    float CurrentWidth = GetScreenWidth();
    float Zoom;
    // std::cout << "Current Height: " << CurrentHeight << std::endl;
    // std::cout << "Current Width: " << CurrentWidth << std::endl;
    // std::cout << m_ScreenSize.x << ", " << m_ScreenSize.y << std::endl;
    if (CurrentWidth / CurrentHeight < (m_ScreenSize.x / m_ScreenSize.y))
    {
        // std::cout << "Width based" << std::endl;
        Zoom = CurrentWidth / m_ScreenSize.x;
    }
    else
    {
        // std::cout << "Height based" << std::endl;
        Zoom = CurrentHeight / m_ScreenSize.y;
    }
    // std::cout << "Zoom: " << Zoom << std::endl;
    Zoom /= 2;
    camera.offset = { 0, Offset * (Zoom) };
    camera.zoom = Zoom;
    BeginMode2D(camera);

    m_Background.render();
    if (m_FlagPole != nullptr)
    {
        m_FlagPole->render();
    }
    for (auto& object : m_EnvironmentInteractive)
    {
        if (object.second == nullptr) continue;
        object.second->Draw();
        if (object.second->getItemID() == Itemtype::MUSHROOM)
        {
            Mushroom* MushroomItem = dynamic_cast<Mushroom*>(object.second);
            if (MushroomItem->isHit()) continue;
            DrawBoundingBox(MushroomItem->GetPosition(), MushroomItem->GetSize(), RED);
        }
        else if (object.second->getItemID() == Itemtype::FIREFLOWER)
        {
            FireFlower* FireFlowerItem = dynamic_cast<FireFlower*>(object.second);
            if (FireFlowerItem->isHit())
            {
                std::cout << "Fire Flower is hitted" << std::endl;
                continue;
            }
            // std::cout << "Position: " << FireFlowerItem->GetPosition().x << ", " << FireFlowerItem->GetPosition().y << std::endl;
            // DrawCircle(FireFlowerItem->GetPosition().x, FireFlowerItem->GetPosition().y, 10, RED);
            DrawBoundingBox(FireFlowerItem->GetPosition(), FireFlowerItem->GetSize(), RED);
        }

    }
    for (auto& object : m_EnvironmentInteractive)
    {
        object.first->render();
    }
    for (auto& object : m_Lifts)
    {
        object->render();
    }
    AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
    DrawBoundingBox(PlayerBox.getPosition(), PlayerBox.getSize(), RED, 10);
    for (auto& object : m_IdleCoin)
    {
        if (object->isHit()) continue;
        object->Draw();
    }
    for (auto& object : m_EndPipes)
    {
        object->render();
    }
    m_FireballHandler.draw();
    float HidePositionX = m_ScreenSize.x * 2;
    for (auto& object : m_Drawables)
    {
        object->render();
    }
    for (auto& object : m_Enemies)
    {
        // if (object->isHit()) continue;
        object->render();
    }
    for (auto& object : m_Environment)
    {
        if (object->getType() == EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE)
        {
            // std::cout << "Warp Pipe at: " << object->m_Position.x << " " << object->m_Position.y << std::endl;
        }
        object->render();
    }
    Ground::GetGround()->render();
    m_Player->Draw();
    m_Player->firePool->Draw();
    DrawRectangle((HidePositionX)+m_CameraPosition.x, -Offset, INT_MAX, INT_MAX, RED);
    EndMode2D();

}
void Level::produceSwitchSignal()
{
    // std::cout << "Is Dead: " << m_Player->isDead() << std::endl;
    // std::cout << "Is Dead Finished: " << m_Player->isDeadFinished() << std::endl;
    // std::cout << "Is Sliding: " << m_Player->isSliding() << std::endl;
    // std::cout << "Is Sliding Finished: " << m_Player->isSlidingFinished() << std::endl;

    if (m_Player->isDead() && m_Player->isDeadFinished())
    {
        if (m_Player->getLives() > 0)
        {
            m_Player->reset();
            m_Mediator->notify(this, LEVEL_RETURN_MESSAGE::RESTART);
        }
        else
        {
            m_Mediator->notify(this, LEVEL_RETURN_MESSAGE::LOSE);
            std::cout << "Notifying Lose" << std::endl; 
        }
    }
    else if (m_Player->haveWon())
    {
        m_Player->reset();
        m_Mediator->notify(this, LEVEL_RETURN_MESSAGE::WIN);
        std::cout << "Notifying Win" << std::endl;

    }
    else if (m_Player->isSlidingFinished())
    {
        m_Player->resetSlidingFinished();
        m_Player->reset();
        m_Mediator->notify(this, LEVEL_RETURN_MESSAGE::HIDDEN);

        std::cout << "Notifying Hidden" << std::endl;

    }
    else if (IsKeyPressed(KEY_LEFT_BRACKET))
    {
        m_Player->reset();
        std::cout << "Notifying Hidden" << std::endl;
        m_Mediator->notify(this, LEVEL_RETURN_MESSAGE::HIDDEN);

    }
}
void Level::update(float DeltaTime)
{
    // std::cout << "Is Player Finished: " << isPlayerFinished << std::endl;
    // std::cout << "In Control: " << m_InControl << std::endl;
    // std::cout << "Touched Flag: " << m_TouchedFlag << std::endl;
    // std::cout << "In End Pipe: " << m_EndPipeHandler.isPlayerInPipe() << std::endl;
    m_Ground->update(m_CameraPosition);
    doPauseLogic();
    if (IsKeyPressed(KEY_O))
    {
        m_TouchedFlag = true;
    }
    if (m_Paused)
    {
        return;
    }

    if (isPlayerFinished)
    {
        InHole control(m_Player);
        control.execute(DeltaTime);
    }
    else if (!isPlayerFinished && m_InControl && !m_TouchedFlag && !m_EndPipeHandler.isPlayerInPipe())
    {
        FullControl control(m_Player);
        control.execute(DeltaTime);
    }
    else if (!isPlayerFinished && m_TouchedFlag)
    {
        Command* control = AutoMove::getInstance(m_Player);
        control->execute(DeltaTime);
    }
    if (m_Player->GetPosition().x > m_CameraPosition.x + m_PlayerOffset)
    {
        float Delta = m_Player->GetPosition().x - m_CameraPosition.x - m_PlayerOffset;
        m_CameraPosition.x += Delta * 0.05;
    }
    if (m_Player->GetPosition().x < m_CameraPosition.x)
    {
        Vector2 NewPosition = { m_CameraPosition.x, m_Player->GetPosition().y };
        m_Player->setPosition(NewPosition);
    }
    m_FireballHandler.update();
    if (m_Ground->m_WorldType == Level::WorldType::OVERWORLD)
    {
        m_Background.update(m_CameraPosition, true);
    }
    else
    {
        m_Background.update(m_CameraPosition, false);
    }
    for (auto& object : m_Environment)
    {
        object->update();
    }
    for (auto& object : m_EnvironmentInteractive)
    {
        object.first->update();
    }
    for (auto& object : m_EnvironmentInteractive)
    {
        if (object.second) object.second->Update(DeltaTime);
    }
    for (auto& object : m_Lifts)
    {
        object->update(DeltaTime);
    }
    m_EnemyHandler.update();
    if (m_EndPipeHandler.update())
    {
        return;
    }
    if (m_FlagPole != nullptr)
    {
        m_FlagPole->update();
    }
    applyBoundaries();
    resolveEnvironmentCollisions();
    resolveInteractiveEnvironmentCollisions();
    handleItemLogic();
    resolveFlagPoleCollisions();
    isPlayerFinished = isPlayerInHole();
    if (m_Player->haveWon())
    {
        // for winning
        // SoundManager::getInstance().PlaySoundEffect(LEVELCOMPLETE_SOUND);
    }
    produceSwitchSignal();

}
bool Level::isPlayerInHole()
{
    for (int i = 0; i < m_Ground->getHoleCount(); i++)
    {
        auto hole = m_Ground->getHole(i);
        if (m_Player->GetPosition().x > hole.first)
        {
            if (m_Player->GetPosition().x + m_Player->GetSize().x < hole.first + hole.second * 100)
            {
                if (m_Player->GetPosition().y + m_Player->GetSize().y > m_Ground->m_Position.y)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
void Level::pauseLevel()
{
    m_Paused = true;
}
void Level::continueLevel()
{
    m_Paused = false;
}
unsigned int Level::doPauseLogic()
{
    if (IsKeyPressed(KEY_P))
    {
        if (m_Paused)
        {
            continueLevel();
            m_Mediator->notify(this, LEVEL_RETURN_MESSAGE::CONTINUE);
        }
        else
        {
            pauseLevel();
            m_Mediator->notify(this, LEVEL_RETURN_MESSAGE::PAUSE);
        }
    }
    if (m_Paused)
    {
        if (IsKeyPressed(KEY_Q))
        {
            m_Mediator->notify(this, LEVEL_RETURN_MESSAGE::QUIT);
        }
        else if (IsKeyPressed(KEY_R))
        {
            m_Mediator->notify(this, LEVEL_RETURN_MESSAGE::RESTART);

        }
    }
    return LEVEL_RETURN_MESSAGE::RUNNING;
}
void Level::reset()
{
    if (m_FlagPole != nullptr)
    {
        delete m_FlagPole;
        m_FlagPole = nullptr;
    }
    m_Enemies.clear();
    for (auto& object : m_Environment)
    {
        if (object) delete object;
    }
    m_Environment.clear();
    for (auto& object : m_EnvironmentInteractive)
    {
        if (object.first) delete object.first;
        if (object.second) delete object.second;
    }
    m_EnvironmentInteractive.clear();
    for (auto& coin : m_IdleCoin)
    {
        if (coin) delete coin;
    }
    m_IdleCoin.clear();
    for (auto& object : m_Drawables)
    {
        if (object) delete object;
    }
    m_Drawables.clear();
    for (auto& object : m_Lifts)
    {
        if (object) delete object;
    }
    m_Lifts.clear();
    for (auto& object : m_EndPipes)
    {
        if (object) delete object;
    }
    m_EndPipes.clear();
    isPlayerFinished = false;
    m_Paused = false;
    m_TouchedFlag = false;
    m_InControl = true;
    m_StartPosition = {0, 0};
    m_TouchedEndPipe = false;
    m_CameraPosition = {0, 0};
    m_EndPipeHandler.reset();
    m_EnemyHandler.reset();
    m_FireballHandler.reset();
    m_InSpecialPipe = false;
    // m_Player->reset();
}
void Level::EndPipeHandler::addEndPipe(EndPipe* Pipe)
{
    m_EndPipes.push_back(Pipe);
}
void Level::EndPipeHandler::attachPlayer(Character* Player)
{
    m_Player = Player;
}
bool Level::EndPipeHandler::update()
{
    if (inPipe)
    {
        std::cout << "In Pipe" << std::endl;
    }
    if (m_Player->isSliding())
    {

    }
    for (int i = 0; i < m_EndPipes.size(); ++i)
    {
        AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
        AABBox EnvironmentBox = AABBox(m_EndPipes[i]->m_Position, m_EndPipes[i]->getSize());
        EnvironmentBox.setFixed(true);
        if (isColliding(PlayerBox, EnvironmentBox))
        {
            if (isCollidingLeft(PlayerBox, EnvironmentBox))
            {
                std::cout << "Sliding Right" << std::endl;
                m_Player ->SlidePipe(slidingDirection::right);
                m_Player ->powerDown();
                m_Player->setPosition(Vector2{m_Player->GetPosition().x, EnvironmentBox.getPosition().y + 20});
                inPipe = true;
            }
            else
            {
                if (isCollidingVertically(PlayerBox, EnvironmentBox))
                {
                    m_Player->resetVelocity();
                    if (isCollidingOnTop(PlayerBox, EnvironmentBox))
                    {
                        m_Player->onPlatform();
                    }
                }
                resolveCollisions(PlayerBox, EnvironmentBox);
                m_Player->setPosition(PlayerBox.getPosition());
                m_EndPipes[i]->m_Position = EnvironmentBox.getPosition();
            }
        }
    }
    return false;
}
void Level::EnemyHandler::update()
{
    if (m_Level->m_Player->isDead()) return;
    for (auto& enemy : m_Level->m_Enemies)
    {
        enemy->update(GetFrameTime());
        if (enemy->getEnemyType() == EnemyType::LAKITU)
        {
            Lakitu* LakituEnemy = dynamic_cast<Lakitu*>(enemy);
            if (LakituEnemy->getIsShoot())
            {
                m_Projectiles.push_back(std::weak_ptr<Projectile>(LakituEnemy->getLastProjectile()));
            }
        }
    }
    // std::cout << "Projectile Count: " << m_Projectiles.size() << std::endl;
    for (auto& projectile : m_Projectiles)
    {
        for (auto &object : m_Level->m_Environment)
        {
            AABBox ProjectileBox = AABBox(projectile.lock()->getPosition(), projectile.lock()->getSize());
            AABBox EnvironmentBox = AABBox(object->m_Position, object->getSize());
            if (isColliding(ProjectileBox, EnvironmentBox))
            {
                projectile.lock()->hit();
            }
        }
        AABBox ProjectileBox = AABBox(projectile.lock()->getPosition(), projectile.lock()->getSize());
        AABBox PlayerBox = AABBox(m_Level->m_Player->GetPosition(), m_Level->m_Player->GetSize());
        if (isColliding(ProjectileBox, PlayerBox))
        {
            if (!(projectile.lock()->isActive())) continue;
            if (m_Level->m_Player->isSuper())
            {
                projectile.lock()->hit();
            }
            else
            {
                projectile.lock()->hit();
                m_Level->m_Player->touchEnemy();
            }
        }
    }
    for (auto& enemy : m_Level->m_Enemies)
    {
        // std::cout << "Is Dead: " << enemy->getIsDead() << std::endl;
        if (m_Level->m_Player->isflick()) continue;
        AABBox EnemyBox = AABBox(enemy->getPosition(), enemy->getSize());
        AABBox PlayerBox = AABBox(m_Level->m_Player->GetPosition(), m_Level->m_Player->GetSize());
        if (isColliding(EnemyBox, PlayerBox))
        {
            if (enemy->getIsDead() || enemy->getIsDying())
            {
                std::cout << "Dead" << std::endl;
                break;
            }
            if (m_Level->m_Player->isSuper())
            {
                enemy->hit();
            }
            if (isCollidingVertically(PlayerBox, EnemyBox))
            {
                enemy->hit();
                // std::cout << "Colliding Vertically" << std::endl;
                m_Level->m_Player->killEnemy();

                EnemyBox.setFixed(true);
                resolveCollisions(PlayerBox, EnemyBox);
                m_Level->m_Player->setPosition(PlayerBox.getPosition());

            }
            else
            {
                if (!m_Level->m_Player->isDead())
                {
                    EnemyBox.setFixed(true);
                    resolveCollisions(PlayerBox, EnemyBox);
                    m_Level->m_Player->setPosition(PlayerBox.getPosition());
                    if (m_Level->m_Player->isSuper())
                    {
                        enemy->hit();
                        std::cout << "Super Kill" << std::endl;
                        // enemy->setDead(true);
                        std::cout << "Is Dead: " << enemy->getIsDead() << std::endl;
                    }
                    else
                    {
                        m_Level->m_Player->touchEnemy();
                    }
                    // std::cout << "Touching Enemy" << std::endl;
                }


            }
        }
    }
}
void Level::FireballHandler::setLevel(Level* level)
{
    m_Level = level;
}
void Level::FireballHandler::update()
{
    // SetTargetFPS(10);
    // m_Fireballs = 
    // std::cout << "Fireball Count: " << m_Fireballs.size() << std::endl;
    for (auto& fireball : m_Level->m_Player->firePool->fireballs)
    {
        if (!fireball.IsActive()) continue;
        // std::cout << "Ball is Active" << std::endl;
        // fireball.position = {10, 10};
        // std::cout << "Position: " << fireball.getPosition().x << ", " << fireball.getPosition().y << std::endl;
        if (fireball.IsActive())
        {
            // std::cout << "Size: " << fireball.getSize().x << ", " << fireball.getSize().y << std::endl;
            // std::cout << "Ground Position: " << m_Level->m_Ground->m_Position.y << std::endl;
            if (fireball.getPosition().y + fireball.getSize().y > m_Level->m_Ground->m_Position.y)
            {
                // std::cout << "Touching Ground" << std::endl;
                bool IsInHole = m_Level->m_Ground->isInHole(AABBox(fireball.getPosition(), fireball.getSize()));
                if (IsInHole)
                {
                    int HoleIndex = m_Level->m_Ground->findHole(AABBox(fireball.getPosition(), fireball.getSize()));
                    std::pair<int, int> Hole = m_Level->m_Ground->getHolePosition(HoleIndex);
                    if (fireball.getPosition().x < Hole.first)
                    {
                        fireball.position.x = Hole.first;
                    }
                    else if (fireball.getPosition().x + fireball.getSize().x > Hole.second)
                    {
                        fireball.position.x = Hole.second - fireball.getSize().x;
                    }
                    if (fireball.getPosition().y + fireball.getSize().y > m_Level->m_Ground->m_Position.y + 160)
                    {
                        fireball.Deactivate();
                    }
                }
                else
                {
                    fireball.position = {fireball.getPosition().x, m_Level->m_Ground->m_Position.y - fireball.getSize().y};
                    fireball.Bounce();
                }
                // std::cout << "Position After Reset: " << fireball.getPosition().x << ", " << fireball.getPosition().y << std::endl;
                
            }
            if (fireball.getPosition().x > m_Level->m_CameraPosition.x + 3000)
            {
                fireball.Deactivate();
            }
            if (fireball.getPosition().x < m_Level->m_Player->GetPosition().x - 1000)
            {
                fireball.Deactivate();
            }
        }
        for (auto& Environment : m_Level->m_Environment)
        {
            AABBox FireballBox = AABBox(fireball.getPosition(), fireball.getSize());
            AABBox EnvironmentBox = AABBox(Environment->m_Position, Environment->getSize());
            EnvironmentBox.setFixed(true);
            if (isColliding(FireballBox, EnvironmentBox))
            {
                if (isCollidingHorizontally(FireballBox, EnvironmentBox))
                {
                    fireball.Deactivate();
                }
                else if (isCollidingVertically(FireballBox, EnvironmentBox))
                {
                    fireball.Bounce();
                }
                resolveCollisions(FireballBox, EnvironmentBox);
                fireball.position = FireballBox.getPosition();
            }
        }
        for (auto& Environment : m_Level->m_EnvironmentInteractive)
        {
            AABBox FireballBox = AABBox(fireball.getPosition(), fireball.getSize());
            AABBox EnvironmentBox = AABBox(Environment.first->m_Position, Environment.first->getSize());
            EnvironmentBox.setFixed(true);
            if (isColliding(FireballBox, EnvironmentBox))
            {
                if (isCollidingHorizontallyRawLess(FireballBox, EnvironmentBox, 20.0f))
                {
                    fireball.Deactivate();
                }
                else if (isCollidingVertically(FireballBox, EnvironmentBox))
                {
                    fireball.Bounce();
                }
                resolveCollisions(FireballBox, EnvironmentBox);
                fireball.position = FireballBox.getPosition();
            }
        }
        for (auto& Enemy : m_Level->m_Enemies)
        {
            if (Enemy->getIsDead()) continue;
            AABBox FireballBox = AABBox(fireball.getPosition(), fireball.getSize());
            AABBox EnemyBox = AABBox(Enemy->getPosition(), Enemy->getSize());
            if (isColliding(FireballBox, EnemyBox))
            {
                fireball.Deactivate();
                Enemy->hit();
            }
        }
    }
}
void Level::FireballHandler::draw()
{
    for (auto& fireball : m_Level->m_Player->firePool->fireballs)
    {
        AABBox FireballBox = AABBox(fireball.getPosition(), fireball.getSize());
        DrawBoundingBox(FireballBox.getPosition(), FireballBox.getSize(), RED, 10);
    }
}
Level::Background::Background()
{
    m_TextureLayer1 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/cloud_lonely.png");
    m_TextureLayer2 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/clouds_mg_1_lightened.png");
    m_TextureLayer3 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/glacial_mountains_lightened.png");
    m_TextureLayer4 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/clouds_bg.png");
    // m_TextureLayer5 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/Background5.png");
    // m_TextureLayer6 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/Background6.png");
    // m_TextureLayer7 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/Background7.png");

    m_TextureLayer8 = LoadTexture("assets/textures/Free Pixel Art Forest/PNG/Background layers/Layer_0000_9.png");
    m_TextureLayer9 = LoadTexture("assets/textures/Free Pixel Art Forest/PNG/Background layers/Layer_0001_8.png");
    m_TextureLayer10 = LoadTexture("assets/textures/Free Pixel Art Forest/PNG/Background layers/Layer_0003_6.png");
    m_TextureLayer11 = LoadTexture("assets/textures/Free Pixel Art Forest/PNG/Background layers/Layer_0005_5.png");
    m_TextureLayer12 = LoadTexture("assets/textures/Free Pixel Art Forest/PNG/Background layers/Layer_0006_4.png");
    m_TextureLayer13 = LoadTexture("assets/textures/Free Pixel Art Forest/PNG/Background layers/Layer_0009_2.png");

}
void Level::Background::update(Vector2 CameraPosition, bool Overworld)
{
    m_Overworld = Overworld;
    Vector2 Move = Vector2Subtract(CameraPosition, m_PreviousCameraPosition);
    m_PreviousCameraPosition = CameraPosition;
    m_Layer1Position = Vector2Add(m_Layer1Position, Vector2Scale(Move, 0.95));
    m_Layer2Position = Vector2Add(m_Layer2Position, Vector2Scale(Move, 0.96));
    m_Layer3Position = Vector2Add(m_Layer3Position, Vector2Scale(Move, 0.98));
    m_Layer4Position = Vector2Add(m_Layer4Position, Vector2Scale(Move, 0.97));

    m_Layer8Position = Vector2Add(m_Layer8Position, Vector2Scale(Move, 0.95));
    m_Layer9Position = Vector2Add(m_Layer9Position, Vector2Scale(Move, 0.96));
    m_Layer10Position = Vector2Add(m_Layer10Position, Vector2Scale(Move, 0.98));
    m_Layer11Position = Vector2Add(m_Layer11Position, Vector2Scale(Move, 0.97));
    m_Layer12Position = Vector2Add(m_Layer12Position, Vector2Scale(Move, 0.95));
    m_Layer13Position = Vector2Add(m_Layer13Position, Vector2Scale(Move, 0.96));


}
void Level::Background::render()
{
    // std::cout << "Layer2 Pos: " << m_Layer2Position.x << " " << m_Layer2Position.y << std::endl;
    if (m_Overworld)
    {
        DrawTextureEx(m_TextureLayer4, m_Layer4Position, 0, 9, WHITE);
        DrawTextureEx(m_TextureLayer3, m_Layer1Position, 0, 9, WHITE);
        DrawTextureEx(m_TextureLayer2, m_Layer2Position, 0, 9, WHITE);
        DrawTextureEx(m_TextureLayer1, m_Layer3Position, 0, 9, WHITE);
    }
    else
    {
        DrawTextureEx(m_TextureLayer13, m_Layer13Position, 0, 7, WHITE);
        DrawTextureEx(m_TextureLayer12, m_Layer12Position, 0, 7, WHITE);
        DrawTextureEx(m_TextureLayer8, m_Layer8Position, 0, 7, WHITE);
        DrawTextureEx(m_TextureLayer9, m_Layer9Position, 0, 7, WHITE);
        DrawTextureEx(m_TextureLayer10, m_Layer10Position, 0, 7, WHITE);
        DrawTextureEx(m_TextureLayer11, m_Layer11Position, 0, 7, WHITE);


    }

}
void Level::resolveFlagPoleCollisions()
{
    if (m_FlagPole == nullptr) return;
    static bool PullDone = false;
    AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
    AABBox EnvironmentBox = AABBox(m_FlagPole->m_Position, m_FlagPole->getSize());
    // std::cout << "Flag Pole Position: " << m_FlagPole.m_Position.x << " " << m_FlagPole.m_Position.y << std::endl;
    // std::cout << "Flag Pole Size: " << m_FlagPole.getSize().x << " " << m_FlagPole.getSize().y << std::endl;
    EnvironmentBox.setFixed(true);
    if (!m_TouchedFlag && isColliding(PlayerBox, EnvironmentBox))
    {
        // std::cout << "Colliding with flag pole" << std::endl;
        resolveCollisions(PlayerBox, EnvironmentBox);
        m_TouchedFlag = true;
        m_Player->setPosition(PlayerBox.getPosition());
        m_FlagPole->m_Position = EnvironmentBox.getPosition();
        m_FlagPole->notifyPull();
        m_Player->setPullFlag(true);
        m_Player->setPosition({ m_Player->GetPosition().x + 50, m_Player->GetPosition().y });
        SoundManager::getInstance().PlaySoundEffect(FLAGDOWN_SOUND);
    }
    PullDone = m_FlagPole->isDone();
    if (PullDone)
    {
        m_Player->setPullFlag(false);
        DrawText("Level Complete", 100, 100, 20, RED);
    }
}

Level101::Level101()
{
    m_LevelID = LevelFactory::LEVEL_101;
    load();
}
Level101::~Level101()
{
}
void Level101::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_101);
}
void Level101::update(float DeltaTime)
{
    bool isOnTopSpecialPipe = [=]()
    {
        auto m_SpecialPipe = m_Environment[2];
        AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
        AABBox PipeBox = AABBox(m_SpecialPipe->m_Position, m_SpecialPipe->getSize());
        float ErrorMargin = 10.0f;
        if (PlayerBox.getPosition().y + PlayerBox.getSize().y + ErrorMargin < PipeBox.getPosition().y)
        {
            return false;
        }
        if (PlayerBox.getPosition().y + PlayerBox.getSize().y > PipeBox.getPosition().y + ErrorMargin)
        {
            return false;
        }
        if (PlayerBox.getPosition().x > PipeBox.getPosition().x && PlayerBox.getPosition().x + PlayerBox.getSize().x < PipeBox.getPosition().x + PipeBox.getSize().x)
        {
            std::cout << "On Top of Special Pipe" << std::endl;
            return true;
        }
        return false;
    }();
    if (isOnTopSpecialPipe && IsKeyPressed(KEY_DOWN))
    {
        std::cout << "Trying Sliding Down" << std::endl;
        m_Player->SlidePipe(slidingDirection::down);
        m_InSpecialPipe = true;
    }
    Level::update(DeltaTime);
}
void Level101::render()
{
    Level::render();
}
Level101* Level101::GetLevel101()
{
    static Level101 level;
    return &level;
}
void Level101::reset()
{
    Level::reset();
    this->setName("Level101");
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_101);
}
LevelTesting::LevelTesting()
{
    m_LevelID = LevelFactory::LEVEL_TESTING;
    load();
}
LevelTesting::~LevelTesting()
{
}
void LevelTesting::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_TESTING);
}
void LevelTesting::update(float DeltaTime)
{
    return Level::update(DeltaTime);
}
void LevelTesting::render()
{
    Level::render();

}
LevelTesting* LevelTesting::GetLevelTesting()
{
    static LevelTesting level;
    return &level;
}
void LevelTesting::reset()
{
    Level::reset();
    this->setName("LevelTesting");
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_TESTING);
}
Level103::Level103()
{
    m_LevelID = LevelFactory::LEVEL_103;
    load();
}
Level103::~Level103()
{
}
Level103* Level103::GetLevel103()
{
    static Level103 level;
    return &level;
}
void Level103::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_103);
}
void Level103::update(float DeltaTime)
{
    return Level::update(DeltaTime);
}
void Level103::render()
{
    Level::render();
}
void Level103::reset()
{
    Level::reset();
    this->setName("Level103");
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_103);
}
HiddenLevel101::HiddenLevel101()
{
    m_LevelID = LevelFactory::HIDDEN_LEVEL_101;
    load();
}
HiddenLevel101::~HiddenLevel101()
{
}
HiddenLevel101* HiddenLevel101::GetHiddenLevel101()
{
    static HiddenLevel101 level;
    return &level;
}
void HiddenLevel101::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::HIDDEN_LEVEL_101);
}
void HiddenLevel101::update(float DeltaTime)
{
    return Level::update(DeltaTime);
}
void HiddenLevel101::render()
{
    Level::render();
}
void HiddenLevel101::reset()
{
    Level::reset();
    this->setName("HiddenLevel101");
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::HIDDEN_LEVEL_101);
}
Level102::Level102()
{
    m_LevelID = LevelFactory::LEVEL_102;
    load();
}
Level102::~Level102()
{
}
Level102* Level102::GetLevel102()
{
    static Level102 level;
    return &level;
}
void Level102::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_102);
}
void Level102::update(float DeltaTime)
{
    return Level::update(DeltaTime);
}
void Level102::render()
{
    Level::render();
}
void Level102::reset()
{
    Level::reset();
    this->setName("Level102");
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_102);
}
HiddenLevel102::HiddenLevel102()
{
    m_LevelID = LevelFactory::HIDDEN_LEVEL_102;
    load();
}
HiddenLevel102::~HiddenLevel102()
{
}
HiddenLevel102* HiddenLevel102::GetHiddenLevel102()
{
    static HiddenLevel102 level;
    return &level;
}
void HiddenLevel102::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::HIDDEN_LEVEL_102);
}
void HiddenLevel102::update(float DeltaTime)
{
    return Level::update(DeltaTime);
}
void HiddenLevel102::render()
{
    Level::render();
}
void HiddenLevel102::reset()
 {
    Level::reset();
    this->setName("HiddenLevel102");
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::HIDDEN_LEVEL_102);
}
HiddenLevel103::HiddenLevel103()
{
    m_LevelID = LevelFactory::HIDDEN_LEVEL_103;
    load();
}
HiddenLevel103::~HiddenLevel103()
{
}
HiddenLevel103* HiddenLevel103::GetHiddenLevel103()
{
    static HiddenLevel103 level;
    return &level;
}
void HiddenLevel103::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::HIDDEN_LEVEL_103);
}
void HiddenLevel103::update(float DeltaTime)
{
    return Level::update(DeltaTime);
}
void HiddenLevel103::render()
{
    Level::render();
}
void HiddenLevel103::reset()
{
    Level::reset();
    this->setName("HiddenLevel103");
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::HIDDEN_LEVEL_103);
}