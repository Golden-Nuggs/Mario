#include <box2d/box2d.h>
#include "Block.h"
#include "Guy.h"

class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void HandleBlockContact(Block* block, Guy* guy);
};