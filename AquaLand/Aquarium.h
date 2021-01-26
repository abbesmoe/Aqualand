/**
 * \file Aquarium.h
 *
 * \author Moez Abbes
 *
 * Class that represent the aquarium.
 *
 * add description here
 * 
 */

#pragma once
#include <memory>
#include <vector>
#include <string>
#include "XmlNode.h"

class CItem;

 /**
  * The aquarium
  */
class CAquarium
{
public:
	/// constructor
	CAquarium();

	/// Draw the aquarium
	void OnDraw(Gdiplus::Graphics* graphics);

	/// Add an item to the aquarium
	void Add(std::shared_ptr<CItem> item);

	/// Test an x,y click location to see if it clicked on some item in the aquarium.
	std::shared_ptr<CItem> HitTest(int x, int y);

	/// move grabbed Item to the end of the list.
	void MoveToFront(std::shared_ptr<CItem> item);

	/// Find the closest item in the aquarium to some other item that is also less
	/// than the maximum possible distance
	std::shared_ptr<CItem> CAquarium::ClosestItem(CItem* closestTo, double within);

	/// Save the aquarium as a .aqua XML file.
	void Save(const std::wstring& filename);

	/// Load the aquarium from a .aqua XML file.
	void Load(const std::wstring& filename);

	/// Clear the aquarium data.
	void Clear();

	/// Handle updates for animation
	void Update(double elapsed);

	/// Get the width of the aquarium
	/// \returns Aquarium width
	int GetWidth() const { return mBackground->GetWidth(); }

	/// Get the height of the aquarium
	/// \returns Aquarium height
	int GetHeight() const { return mBackground->GetHeight(); }

private:
	std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image to use

	/// All of the items to populate our aquarium
	std::vector<std::shared_ptr<CItem> > mItems;

	/// Handle an item node.
	void XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node);

	
};

