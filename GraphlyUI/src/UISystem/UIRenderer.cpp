#include "UIRenderer.h"
#include "GraphicsSystem/GraphicsSystem.h"
#include "GraphlyUI/UISystem/Window/UIElement/UIElement.h"
#include "GraphlyMath/GraphlyMath.h"

#include <algorithm>

using namespace GraphlyUI;
using namespace GraphlyMath;
using namespace D2D1;

UIRenderer::UIRenderer(GraphicsSystem* graphicsSystem)
: _graphicsSystem(graphicsSystem)
{}

void UIRenderer::Render(UIElement* element)
{
	auto d2dDevice = _graphicsSystem->GetD2DSystem()->GetD2DDevice();

	// Get local and parent world transforms
	D2D1_MATRIX_3X2_F localTransform = element->GetTransform().GetMatrix();
	D2D1_MATRIX_3X2_F parentTransform = Matrix3x2F::Identity();
	if (element->GetParent())
		parentTransform = element->GetParent()->GetWorldTransform();

	/*
	* The position of the child element is at parentTransform* localTransform
	* because (x, y) child (world) = (x, y) parent (world) + localTransform (user set)
	* so we multply the transform matrices to get the correct position
	*/
	D2D1_MATRIX_3X2_F worldTransform = parentTransform * localTransform;
	element->SetWorldTransform(worldTransform);
	// Set the world space transform to use local space for clipping and rendering
	d2dDevice->SetTransform(worldTransform);

	// Use local space here (space was transformed above)
	d2dDevice->PushAxisAlignedClip(Vector4
	(
		0.0f,
		0.0f,
		element->GetUISettings().dimension.GetX(),
		element->GetUISettings().dimension.GetY()
	));

	element->Render();
	for (const auto& [name, child] : *element)
		Render(child.get());

	d2dDevice->PopAxisAlignedClip();
}

const D2D1_POINT_2F UIRenderer::TransformPoint(const D2D1_MATRIX_3X2_F& m, const Vector2& point) const
{
	return D2D1_POINT_2F
	(
		point.GetX() * m._11 + point.GetY() * m._21 + m._31,
		point.GetX() * m._12 + point.GetY() * m._22 + m._32
	);
}
