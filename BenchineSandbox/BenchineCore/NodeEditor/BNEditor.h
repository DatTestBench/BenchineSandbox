#pragma once
#include <string>
#include "NodeEditor/BNEditorHelpers.h"

class BNEditor final
{
public:
	BNEditor(const std::string& editorName);
	~BNEditor();
	DEL_ROF(BNEditor)

	void Initialize();
	void Update(float dT);
	const Node* AddNode(const Node& node) noexcept;

private:
	std::string m_EditorName;
	bool m_FirstFrame; // Flag set for first frame only, some actions need to be executed only once
	uint32_t m_NextLinkId;

	std::vector<Node> m_Nodes;
	std::vector<Link> m_Links;

#pragma region InternalHelpers
	/*FindNode*/

	/*FindLink*/

	/*FindPin*/

	/*IsPinLinked*/

	/*CanConnect*/

	/*SetPinSides*/
	
#pragma endregion InternalHelpers

	

};