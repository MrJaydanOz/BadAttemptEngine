#include "BAE/BAE_Engine.h"

using namespace bae;

void BAE_Start()
{
	Transform* testTransform1 = Game::GetScene()->AddNode<Transform>("Test1");
	Transform* testTransform2 = testTransform1->AddChild<Transform>("Test2");
	testTransform2->SetLocalPosition(Vector2F(1.0f, 0.0f));
	DEBUG_LOG_INFO("Created 'Test1'");
}

void BAE_Update()
{
	DEBUG_LOG_INFO("----------------------------");

	for (Node* node : Game::GetScene()->GetRootNodes())
	{
		DEBUG_LOG_INFO(DEBUG_NODE_NAME(node));
	}

	Transform* testTransform1 = Game::GetScene()->FindNodeWithName<Transform>("Test1");
	if (!testTransform1)
	{
		DEBUG_LOG_ERROR("Didn't find 'Test1'");
		return;
	}
	DEBUG_LOG_INFO("Found 'Test1'");

	Transform* testTransform2 = Game::GetScene()->FindNodeWithName<Transform>("Test2");
	if (!testTransform2)
	{
		DEBUG_LOG_ERROR("Didn't find 'Test2'");
		return;
	}
	DEBUG_LOG_INFO("Found 'Test2'");

	testTransform1->SetLocalPosition(testTransform1->GetLocalPosition() + Vector2F(1.0f, 0.0f));
	testTransform1->SetLocalRotation(testTransform1->GetLocalRotation() + 1.0f);

	DEBUG_LOG_INFO("'Test1' at " << testTransform1->GetPosition());
	DEBUG_LOG_INFO("'Test2' at " << testTransform2->GetPosition());
}

void BAE_LateUpdate()
{

}

void BAE_PhysicsUpdate()
{

}

void BAE_End()
{
	DEBUG_LOG_INFO("Bye");
}