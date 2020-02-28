#include <box2d/box2d.h>
#include "Block.h"

class ContactListener : public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;
	void HandleBlockContact(Block* block);
};