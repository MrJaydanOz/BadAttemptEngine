#include "GameStateLevel.h"
#include "BAE/BAE_Time.h"

void GameStateDiedScreen::OnStart(ParameterType machine)
{
	bae::Scene& scene = *bae::Game::GetScene();

	bae::Vector2I screenSize = bae::Game::GetGraphics()->GetScreenSize();
	bae::Vector2F screenSizef = (bae::Vector2F)screenSize;

	titleFont = bae::Font::Load("Content/Fonts/Roboto/Roboto-Medium.ttf", 64);
	buttonFont = bae::Font::Load("Content/Fonts/Roboto/Roboto-Medium.ttf", 32);

	title = scene.AddNode<bae::Text>("Title");
	title->offset = bae::PoseF((screenSizef * 0.5f) + bae::Vector2F(0.0f, 128.0f), 0.0f);
	title->font = titleFont;
	title->isUI = true;
	title->text = "Score: " + std::to_string(machine.b.lastGameScore);

	playButton.center = (screenSizef * 0.5f) + bae::Vector2F(0.0f, 32.0f);
	playButton.size = bae::Vector2F(96.0f, 48.0f);
	playText = scene.AddNode<bae::Text>("Play Text");
	playText->offset = bae::PoseF(playButton.center, 0.0f);
	playText->font = buttonFont;
	playText->isUI = true;
	playText->text = "Play Again";

	quitButton.center = (screenSizef * 0.5f) + bae::Vector2F(0.0f, -32.0f);
	quitButton.size = bae::Vector2F(96.0f, 48.0f);
	quitText = scene.AddNode<bae::Text>("Exit Text");
	quitText->offset = bae::PoseF(quitButton.center, 0.0f);
	quitText->font = buttonFont;
	quitText->isUI = true;
	quitText->text = "Main Menu";
}

void GameStateDiedScreen::OnTick(ParameterType machine)
{
	bae::Vector2F mousePosition = (bae::Vector2F)bae::Game::GetInput()->GetMousePixel();
	mousePosition = bae::Game::GetGraphics()->PixelToScreenPoint(mousePosition);
	bool mouseClick = bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_LMB);

	switch (ProcessMenuButton(mousePosition, mouseClick, playButton, playText))
	{
	case ButtonState::CLICKED:
		machine.a.QueueState("Game");
		return;
	}

	switch (ProcessMenuButton(mousePosition, mouseClick, quitButton, quitText))
	{
	case ButtonState::CLICKED:
		machine.a.QueueState("MainMenu");
		return;
	}
}

void GameStateDiedScreen::OnEnd(ParameterType machine)
{
	delete titleFont;
	delete buttonFont;

	bae::Destroy(title);
	bae::Destroy(playText);
	bae::Destroy(quitText);
}

void GameStateLevel::OnStart(ParameterType machine)
{
	enemySpawnRate = 0.3f;
	enemySpawnTimer = 1.0f;
	playerShootCooldown = 0.0f;
	playerFireRate = 5.0f;
	score = 0;
	loseCountdown = 0.0f;
	isPaused = false;

	bae::Time& time = *bae::Game::GetTime();
	bae::Scene& scene = *bae::Game::GetScene();
	bae::Graphics& graphics = *bae::Game::GetGraphics();

	bae::Vector2I screenSize = bae::Game::GetGraphics()->GetScreenSize();
	bae::Vector2F screenSizef = (bae::Vector2F)screenSize;

	graphics.SetBackgroundColor(0x333344FF);

	time.SetTimeScale(1.0f);

	graphics.camera.size = 1.0f;
	graphics.camera.sizeAxisFactor = 0.0f;
	graphics.camera.center = bae::PoseF({ 0.0f, 0.0f }, 0.0f);

	uIFont = bae::Font::Load("Content/Fonts/Roboto/Roboto-Medium.ttf", 48);
	titleFont = bae::Font::Load("Content/Fonts/Roboto/Roboto-Medium.ttf", 64);
	buttonFont = bae::Font::Load("Content/Fonts/Roboto/Roboto-Medium.ttf", 32);

	scoreText = scene.AddNode<bae::Text>("Score Text");
	scoreText->offset = bae::PoseF(screenSizef - bae::Vector2F(8.0f, 8.0f), 0.0f);
	scoreText->pivot = bae::Vector2F(1.0f, 1.0f);
	scoreText->font = uIFont;
	scoreText->isUI = true;
	scoreText->text = "0";
	scoreText->SetZIndex(1000);

	pauseTitle = scene.AddNode<bae::Text>("Title");
	pauseTitle->offset = bae::PoseF((screenSizef * 0.5f) + bae::Vector2F(0.0f, 128.0f), 0.0f);
	pauseTitle->font = titleFont;
	pauseTitle->isUI = true;
	pauseTitle->text = "Paused";
	pauseTitle->SetEnabledSelf(false);
	pauseTitle->SetZIndex(1000);

	pauseResumeButton.center = (screenSizef * 0.5f) + bae::Vector2F(0.0f, 32.0f);
	pauseResumeButton.size = bae::Vector2F(96.0f, 48.0f);
	pauseResumeText = scene.AddNode<bae::Text>("Resume Text");
	pauseResumeText->offset = bae::PoseF(pauseResumeButton.center, 0.0f);
	pauseResumeText->font = buttonFont;
	pauseResumeText->isUI = true;
	pauseResumeText->text = "Resume";
	pauseResumeText->SetEnabledSelf(false);
	pauseResumeText->SetZIndex(1000);

	pauseExitButton.center = (screenSizef * 0.5f) + bae::Vector2F(0.0f, -32.0f);
	pauseExitButton.size = bae::Vector2F(96.0f, 48.0f);
	pauseExitText = scene.AddNode<bae::Text>("Exit Text");
	pauseExitText->offset = bae::PoseF(pauseExitButton.center, 0.0f);
	pauseExitText->font = buttonFont;
	pauseExitText->isUI = true;
	pauseExitText->text = "Main Menu";
	pauseExitText->SetEnabledSelf(false);
	pauseExitText->SetZIndex(1000);

	playerSprites = bae::Image::Load("Content/Sprites/PlayerSprites.png");
	basicEnemySprites = bae::Image::Load("Content/Sprites/BasicEnemySprites.png");
	rollingEnemySprites = bae::Image::Load("Content/Sprites/RollingEnemySprites.png");
	mortarEnemySprites = bae::Image::Load("Content/Sprites/MortarEnemySprites.png");
	playerBulletSprites = bae::Image::Load("Content/Sprites/PlayerBulletSprites.png");
	basicEnemyBulletSprites = bae::Image::Load("Content/Sprites/BasicEnemyBulletSprites.png");
	collectableSprites = bae::Image::Load("Content/Sprites/CollectableSprites.png");

	playerShadows = bae::Image::Load("Content/Sprites/PlayerShadows.png");
	basicEnemyShadows = bae::Image::Load("Content/Sprites/BasicEnemyShadows.png");
	rollingEnemyShadows = bae::Image::Load("Content/Sprites/RollingEnemyShadows.png");
	mortarEnemyShadows = bae::Image::Load("Content/Sprites/MortarEnemyShadows.png");

	using CreateStateT = in_initializer_list<bae::AnimationControl*>;

	bae::AnimationState* state = nullptr;
	// Path to node from Animator node.
	auto animationControl = bae::AnimationControlSpriteImage({});

	auto asShadow = [&](in<bae::Image*> spriteSheet) -> bae::AnimationControlSpriteImage*
		{
			bae::AnimationControlSpriteImage* c = new bae::AnimationControlSpriteImage(animationControl);
			c->nodePath = { "Shadow" };
			c->image = spriteSheet;

			return c;
		};

	playerAnimation = new bae::Animation();
	{
		// AnimationControl settings.
		animationControl.nodePath = { "Sprite" };
		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 8;
		animationControl.frameRate = 8.0f;
		animationControl.image = playerSprites;
		// Add an AnimationState with the AnimationControl in it.
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			playerAnimation->CreateState<bae::AnimationState, CreateStateT>("idle r" + std::to_string(i), 
				{ new bae::AnimationControlSpriteImage(animationControl), asShadow(playerShadows) });
			animationControl.clipStartPosition.y += 32;
		}

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 8;
		animationControl.frameRate = 24.0f;
		animationControl.image = playerSprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			playerAnimation->CreateState<bae::AnimationState, CreateStateT>("walk r" + std::to_string(i), 
				{ new bae::AnimationControlSpriteImage(animationControl), asShadow(playerShadows) });
			animationControl.clipStartPosition.y += 32;
		}

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 6;
		animationControl.frameRate = 24.0f;
		animationControl.image = playerSprites;
		animationControl.clipStartPosition = bae::Vector2I(32 * 8, 0);
		LOOP(i, 16)
		{
			state = playerAnimation->CreateState<bae::AnimationState, CreateStateT>("shoot r" + std::to_string(i), 
				{ new bae::AnimationControlSpriteImage(animationControl), asShadow(playerShadows) });
			state->changeToStateAfterDuration = playerAnimation->GetState("idle r" + std::to_string(i));
			state->duration = 6.0f / 24.0f;
			animationControl.clipStartPosition.y += 32;
		}
	}

	playerBulletAnimation = new bae::Animation();
	{
		animationControl.clipSize = bae::Vector2I(16, 16);
		animationControl.frameCount = 1;
		animationControl.frameRate = 1.0f;
		animationControl.image = playerBulletSprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);

		playerBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("inair", 
			{ new bae::AnimationControlSpriteImage(animationControl) });

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.clipFrameDelta = bae::Vector2I(0, 32);
		animationControl.frameCount = 4;
		animationControl.frameRate = 12.0f;
		animationControl.image = playerBulletSprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 16);

		state = playerBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("impact", 
			{ new bae::AnimationControlSpriteImage(animationControl) });
		state->changeToStateAfterDuration = nullptr;
		state->duration = 4.0f / 12.0f;
		animationControl.clipFrameDelta = {};

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 4;
		animationControl.frameRate = 24.0f;
		animationControl.image = playerBulletSprites;
		animationControl.clipStartPosition = bae::Vector2I(32, 0);
		LOOP(i, 16)
		{
			state = playerBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("fire r" + std::to_string(i), 
				{ new bae::AnimationControlSpriteImage(animationControl) });
			state->changeToStateAfterDuration = nullptr;
			state->duration = 4.0f / 24.0f;
			animationControl.clipStartPosition.y += 32;
		}
	}

	basicEnemyAnimation = new bae::Animation();
	{
		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 8;
		animationControl.frameRate = 8.0f;
		animationControl.image = basicEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			basicEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("idle r" + std::to_string(i), 
				{ new bae::AnimationControlSpriteImage(animationControl), asShadow(basicEnemyShadows) });
			animationControl.clipStartPosition.y += 32;
		}

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 8;
		animationControl.frameRate = 24.0f;
		animationControl.image = basicEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			basicEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("walk r" + std::to_string(i), 
				{ new bae::AnimationControlSpriteImage(animationControl), asShadow(basicEnemyShadows) });
			animationControl.clipStartPosition.y += 32;
		}

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 6;
		animationControl.frameRate = 24.0f;
		animationControl.image = basicEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(32 * 8, 0);
		LOOP(i, 16)
		{
			state = basicEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("shoot r" + std::to_string(i), 
				{ new bae::AnimationControlSpriteImage(animationControl), asShadow(basicEnemyShadows) });
			state->changeToStateAfterDuration = basicEnemyAnimation->GetState("idle r" + std::to_string(i));
			state->duration = 6.0f / 24.0f;
			animationControl.clipStartPosition.y += 32;
		}
	}

	mortarEnemyAnimation = new bae::Animation();
	{
		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 8;
		animationControl.frameRate = 8.0f;
		animationControl.image = mortarEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			mortarEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("idle r" + std::to_string(i), 
				{ new bae::AnimationControlSpriteImage(animationControl), asShadow(mortarEnemyShadows) });
			animationControl.clipStartPosition.y += 32;
		}

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 8;
		animationControl.frameRate = 24.0f;
		animationControl.image = mortarEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			mortarEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("walk r" + std::to_string(i), 
				{ new bae::AnimationControlSpriteImage(animationControl), asShadow(mortarEnemyShadows) });
			animationControl.clipStartPosition.y += 32;
		}

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 6;
		animationControl.frameRate = 24.0f;
		animationControl.image = mortarEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(32 * 8, 0);
		LOOP(i, 16)
		{
			state = mortarEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("shoot r" + std::to_string(i), 
				{ new bae::AnimationControlSpriteImage(animationControl), asShadow(mortarEnemyShadows) });
			state->changeToStateAfterDuration = mortarEnemyAnimation->GetState("idle r" + std::to_string(i));
			state->duration = 6.0f / 24.0f;
			animationControl.clipStartPosition.y += 32;
		}
	}

	rollingEnemyAnimation = new bae::Animation();
	{
		animationControl.clipSize = bae::Vector2I(64, 64);
		animationControl.frameCount = 12;
		animationControl.frameRate = 12.0f;
		animationControl.image = rollingEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			rollingEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("roll r" + std::to_string(i), 
				{ new bae::AnimationControlSpriteImage(animationControl), asShadow(rollingEnemyShadows) });
			animationControl.clipStartPosition.y += 64;
		}

		animationControl.clipSize = bae::Vector2I(64, 64);
		animationControl.frameCount = 12;
		animationControl.frameRate = 12.0f;
		animationControl.image = rollingEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(64 * 12, 0);
		LOOP(i, 16)
		{
			rollingEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("blink r" + std::to_string(i), 
				{ new bae::AnimationControlSpriteImage(animationControl), asShadow(rollingEnemyShadows) });
			animationControl.clipStartPosition.y += 64;
		}
	}

	basicEnemyBulletAnimation = new bae::Animation();
	{
		animationControl.clipSize = bae::Vector2I(16, 16);
		animationControl.frameCount = 1;
		animationControl.frameRate = 1.0f;
		animationControl.image = basicEnemyBulletSprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);

		basicEnemyBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("inair", 
			{ new bae::AnimationControlSpriteImage(animationControl) });

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.clipFrameDelta = bae::Vector2I(0, 32);
		animationControl.frameCount = 4;
		animationControl.frameRate = 12.0f;
		animationControl.image = basicEnemyBulletSprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 16);

		state = basicEnemyBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("impact", 
			{ new bae::AnimationControlSpriteImage(animationControl) });
		state->changeToStateAfterDuration = nullptr;
		state->duration = 4.0f / 12.0f;
		animationControl.clipFrameDelta = {};

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 4;
		animationControl.frameRate = 24.0f;
		animationControl.image = basicEnemyBulletSprites;
		animationControl.clipStartPosition = bae::Vector2I(32, 0);
		LOOP(i, 16)
		{
			state = basicEnemyBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("fire r" + std::to_string(i), 
				{ new bae::AnimationControlSpriteImage(animationControl) });
			state->changeToStateAfterDuration = nullptr;
			state->duration = 4.0f / 24.0f;
			animationControl.clipStartPosition.y += 32;
		}
	}

	collectableAnimation = new bae::Animation();
	{
		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 10;
		animationControl.frameRate = 24.0f;
		animationControl.image = collectableSprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);

		collectableAnimation->CreateState<bae::AnimationState, CreateStateT>("spin",
			{ new bae::AnimationControlSpriteImage(animationControl) });

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.clipFrameDelta = bae::Vector2I(-32, 0);
		animationControl.frameCount = 10;
		animationControl.frameRate = 24.0f;
		animationControl.image = collectableSprites;
		animationControl.clipStartPosition = bae::Vector2I(32 * 9, 0);

		collectableAnimation->CreateState<bae::AnimationState, CreateStateT>("spinr",
			{ new bae::AnimationControlSpriteImage(animationControl) });
		animationControl.clipFrameDelta = {};
	}

	player = scene.AddNode<PlayerCharacter>("Player");
	player->Setup(*this);
}

void GameStateLevel::OnTick(ParameterType machine)
{
	bae::Time& time = *bae::Game::GetTime();
	bae::Input& input = *bae::Game::GetInput();
	bae::Graphics& graphics = *bae::Game::GetGraphics();
	bae::Scene& scene = *bae::Game::GetScene();
	bae::Physics& physics = *bae::Game::GetPhysics();

	if (isPaused)
	{
		auto resume = [&]() -> void
			{
				isPaused = false;

				pauseTitle->SetEnabledSelf(false);
				pauseResumeText->SetEnabledSelf(false);
				pauseExitText->SetEnabledSelf(false);

				time.SetTimeScale(1.0f);
			};

		if (input.KeyPressed(bae::KeyCode::KEYCODE_ESCAPE))
		{
			resume();
			return;
		}

		bae::Vector2F mousePosition = (bae::Vector2F)bae::Game::GetInput()->GetMousePixel();
		mousePosition = bae::Game::GetGraphics()->PixelToScreenPoint(mousePosition);
		bool mouseClick = bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_LMB);

		switch (ProcessMenuButton(mousePosition, mouseClick, pauseResumeButton, pauseResumeText))
		{
		case ButtonState::CLICKED:
			resume();
			return;
		}

		switch (ProcessMenuButton(mousePosition, mouseClick, pauseExitButton, pauseExitText))
		{
		case ButtonState::CLICKED:
			machine.a.QueueState("MainMenu");
			return;
		}
	}
	else
	{
		if (input.KeyPressed(bae::KeyCode::KEYCODE_ESCAPE))
		{
			isPaused = true;

			pauseTitle->SetEnabledSelf(true);
			pauseResumeText->SetEnabledSelf(true);
			pauseExitText->SetEnabledSelf(true);

			time.SetTimeScale(0.0f);
			return;
		}

		bae::Vector2F inputDirection = bae::Vector2F(0, 0);

		if (bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_W)) inputDirection.y++;
		if (bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_S)) inputDirection.y--;
		if (bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_A)) inputDirection.x--;
		if (bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_D)) inputDirection.x++;

		player->MoveWithInput(inputDirection);

		bae::Vector2F aimDirection = (bae::Vector2F)graphics.PixelToScreenPoint(input.GetMousePixel()) - graphics.WorldToScreenPoint(player->GetPosition());
		aimDirection /= aimDirection.Magnitude();

		if (effects.size() > 0)
		{
			bool someDeletion = false;
			for (Effect*& i : effects)
			{
				if (i->IsDone())
				{
					bae::Destroy(i);
					i = nullptr;
					someDeletion = true;
				}
			}

			if (someDeletion)
				effects.RemoveWhere([](in<Effect*> effect) -> bool { return effect == nullptr; });
		}

		if (basicBullets.size() > 0)
		{
			bae::List<bae::PhysicsCollision> collisions;

			bool someDeletion = false;
			for (ref<BasicBullet*> i : basicBullets)
			{
				if ((i->lifeTime -= time.DeltaTime()) <= 0.0f || i->animator->GetCurrentState() == nullptr)
				{
					bae::Destroy(i);
					i = nullptr;
					someDeletion = true;
				}
				else if (i->animator->GetCurrentState()->GetKey().starts_with("inair"))
				{
					physics.FindCollisionsOf(i, collisions);
					for (in<bae::PhysicsCollision> collision : collisions)
					{
						EnemyCharacter** enemyResult;
						if (enemies.TryFindIf([&](in<EnemyCharacter*> enemy) -> bool { return enemy == collision.physicsBody2; }, enemyResult))
						{
							i->animator->Play("impact");
							i->SetVelocity(bae::Vector2F(0.0f, 0.0f));

							(*enemyResult)->Damage(i->damage);
						}

						if (player == collision.physicsBody2)
						{
							i->animator->Play("impact");
							i->SetVelocity(bae::Vector2F(0.0f, 0.0f));

							player->Damage(i->damage);
						}
					}
					collisions.Clear();
				}
			}

			if (someDeletion)
			{
				basicBullets.RemoveWhere([](in<BasicBullet*> bullet) -> bool { return bullet == nullptr; });
			}
		}

		if (enemies.size() > 0)
		{
			bool someDeletion = false;
			for (ref<EnemyCharacter*> i : enemies)
			{
				i->Tick(*this);

				if (i->healthBar->currentHealth < 0.0f)
				{
					i->Die(*this);
					bae::Destroy(i);
					i = nullptr;
					someDeletion = true;
				}
			}

			if (someDeletion)
				enemies.RemoveWhere([](in<EnemyCharacter*> enemy) -> bool { return enemy == nullptr; });
		}

		if (collectables.size() > 0)
		{
			bae::List<bae::PhysicsCollision> collisions;

			bool someDeletion = false;
			for (ref<Collectable*> i : collectables)
			{
				physics.FindCollisionsOf(i, collisions);
				for (in<bae::PhysicsCollision> collision : collisions)
				{
					if (player == collision.physicsBody2)
					{
						i->Collect(*this);
						bae::Destroy(i);
						i = nullptr;
					}
				}
				collisions.Clear();
			}

			if (someDeletion)
				collectables.RemoveWhere([](in<Collectable*> collectable) -> bool { return collectable == nullptr; });
		}

		scoreText->text = std::to_string(score);

		if (player->healthBar->currentHealth <= 0.0f)
		{
			loseCountdown += time.UnscaledDeltaTime();
			time.SetTimeScale(0.05f);
		}

		if (loseCountdown > 3.0f)
		{
			machine.b.lastGameScore = score;
			machine.a.QueueState("DiedScreen");
			return;
		}

		enemySpawnRate += time.DeltaTime() * 0.001f;
		enemySpawnTimer -= time.DeltaTime();

		if (enemySpawnTimer <= 0.0f)
		{
			enemySpawnTimer = 1.0f / enemySpawnRate;

			int random = rand() % 8;

			EnemyCharacter* newEnemy;

			switch (random)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				newEnemy = scene.AddNode<BasicEnemy>("Basic Enemy");
				newEnemy->SetPosition(player->GetPosition() + bae::Vector2F(0.0f, 350.0f).Rotate(rand() % 360));
				newEnemy->Setup(*this);
				enemies.Append(newEnemy);
				break;
			case 4:
			case 5:
				newEnemy = scene.AddNode<ShotgunEnemy>("Shotgun Enemy");
				newEnemy->SetPosition(player->GetPosition() + bae::Vector2F(0.0f, 350.0f).Rotate(rand() % 360));
				newEnemy->Setup(*this);
				enemies.Append(newEnemy);
				break;
			case 6:
			case 7:
				newEnemy = scene.AddNode<RollingEnemy>("Rolling Enemy");
				newEnemy->SetPosition(player->GetPosition() + bae::Vector2F(0.0f, 350.0f).Rotate(rand() % 360));
				newEnemy->Setup(*this);
				enemies.Append(newEnemy);
				break;
			}
		}

		if (playerShootCooldown > 0.0f)
		{
			playerShootCooldown -= bae::Game::GetTime()->DeltaTime();
		}

		if (input.KeyHeld(bae::KeyCode::KEYCODE_LMB) && playerShootCooldown <= 0.0f)
		{
			playerShootCooldown += 1.0f / playerFireRate;

			BasicBullet* bullet = scene.AddNode<BasicBullet>("Bullet");
			bullet->SetPosition(player->GetPosition() + (aimDirection * 8.0f));
			bullet->SetVelocity(aimDirection * 400.0f);
			bullet->collider->size = bae::Vector2F(6.0f, 6.0f);
			bullet->collider->collisionLayers = 0b0100;
			bullet->collider->isTrigger = true;
			bullet->animator->SetAnimation(playerBulletAnimation);
			bullet->animator->Play("inair");
			bullet->damage = 26.0f;
			bullet->lifeTime = 3.0f;
			basicBullets.Append(bullet);

			Effect* muzzleFlash = scene.AddNode<Effect>("Flash");
			muzzleFlash->sprite->offset = bae::PoseF(player->GetPosition() + (aimDirection * 8.0f), 0.0f);
			muzzleFlash->SetAnimation(playerBulletAnimation);
			muzzleFlash->Play("fire r" + std::to_string(bae::Mod(Character::GetDirectionAnimationIndex(aimDirection) + 8, 16)));
			effects.Append(muzzleFlash);

			player->UpdateAnimation(aimDirection, true);
		}
		else
			player->UpdateAnimation(aimDirection, false);

		graphics.camera.center.position = bae::Lerp(graphics.camera.center.position, player->GetPosition(), 0.025f);
		graphics.camera.size = bae::Lerp(graphics.camera.size, 512.0f, 0.025f);
	}
}

void GameStateLevel::CreateCollectable(in<bae::Vector2F> position)
{
	bae::Scene& scene = *bae::Game::GetScene();

	int random = rand() % 16;

	Collectable* newCollectable;

	switch (random)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
		newCollectable = scene.AddNode<PointsCollectable>("Points Collectable");
		newCollectable->SetPosition(position);
		newCollectable->Setup(*this);
		collectables.Append(newCollectable);
		break;
	case 12:
	case 13:
		newCollectable = scene.AddNode<HealthCollectable>("Health Collectable");
		newCollectable->SetPosition(position);
		newCollectable->Setup(*this);
		collectables.Append(newCollectable);
		break;
	case 14:
		newCollectable = scene.AddNode<SpeedCollectable>("Speed Collectable");
		newCollectable->SetPosition(position);
		newCollectable->Setup(*this);
		collectables.Append(newCollectable);
		break;
	case 15:
		newCollectable = scene.AddNode<FireRateCollectable>("Fire Rate Collectable");
		newCollectable->SetPosition(position);
		newCollectable->Setup(*this);
		collectables.Append(newCollectable);
		break;
	}
}

void GameStateLevel::OnEnd(ParameterType machine)
{
	bae::Time& time = *bae::Game::GetTime();
	bae::Graphics& graphics = *bae::Game::GetGraphics();

	graphics.SetBackgroundColor(0x000000FF);

	time.SetTimeScale(1.0f);

	delete uIFont;
	delete titleFont;
	delete buttonFont;

	bae::Destroy(scoreText);
	bae::Destroy(pauseTitle);
	bae::Destroy(pauseResumeText);
	bae::Destroy(pauseExitText);

	delete playerAnimation;
	delete basicEnemyAnimation;
	delete rollingEnemyAnimation;
	delete mortarEnemyAnimation;
	delete playerBulletAnimation;
	delete basicEnemyBulletAnimation;
	delete collectableAnimation;

	delete playerSprites;
	delete basicEnemySprites;
	delete rollingEnemySprites;
	delete mortarEnemySprites;
	delete playerBulletSprites;
	delete basicEnemyBulletSprites;
	delete collectableSprites;

	delete playerShadows;
	delete basicEnemyShadows;
	delete rollingEnemyShadows;
	delete mortarEnemyShadows;

	bae::Destroy(player);
	for (bae::Node* node : basicBullets)
		bae::Destroy(node);
	basicBullets.Clear();

	for (bae::Node* node : effects)
		bae::Destroy(node);
	effects.Clear();

	for (bae::Node* node : enemies)
		bae::Destroy(node);
	enemies.Clear();

	for (bae::Node* node : collectables)
		bae::Destroy(node);
	collectables.Clear();
}
