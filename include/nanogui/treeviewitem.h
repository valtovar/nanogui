#pragma once

#include <nanogui/label.h>

#include <list>


NAMESPACE_BEGIN(nanogui)

class TreeView;

//! Node for gui tree view
class NANOGUI_EXPORT TreeViewItem : public Label
{
  friend class TreeView;
  const size_t mNodeId;

public:
  using NodeId = size_t;
  enum { RootNodeId = 0xfefefefe, BadNodeId = 0xffffffff };
  using NodeList = std::list<NodeId>;

  explicit TreeViewItem(Widget* widget);
  ~TreeViewItem() override;

  TreeView* source() const;
  TreeViewItem* baseNode() const;

  Widget* previewArea() { return mPreviewArea; }

  Vector2i preferredSize(NVGcontext *ctx) const override;

  int getIcon() const { return mIcon; }
  void setIcon( int icon );

  int imageIndex() const { return mImageIndex; }
  void setImageIndex( int imageIndex ) { mImageIndex = imageIndex; }
  int selectedImageIndex() const { return SelectedImageIndex; }
  void setSelectedImageIndex( int imageIndex ) { SelectedImageIndex = imageIndex; }

  void* getData() const { return Data; }
  void setData( void* data ) { Data = data; }
  void setAnchorPosition(const Vector2i& pos) { mAnchorPotsition = pos; }
  const Vector2i anchorPosition() const { return mAnchorPotsition; }

  int nodesCount() const;
  bool hasNodes() const;

  bool isAliveId(NodeId id);

  void removeChild(const Widget *widget) override;
  void removeNode(const Widget* node);

  NodeId getNodeId() const { return mNodeId; }

  //! Adds a new node behind the last child node.
  //! \param text text of the new node
  //! \param icon icon text of the new node
  //! \param imageIndex index of the image for the new node (-1 = none)
  //! \param selectedImageIndex index of the selected image for the new node (-1 = same as imageIndex)
  //! \param data user data (void*) of the new node
  //! \param data2 user data2 (IReferenceCounted*) of the new node
  //! \return
  //! returns the new node
  TreeViewItem* addNodeBack(
    const std::string& text,
    int icon = -1,
    int imageIndex = -1,
    int selectedImageIndex = -1,
    void* data = nullptr);

  TreeViewItem* addNode(
    const std::string& text,
    int icon = -1,
    int imageIndex = -1,
    int selectedImageIndex = -1,
    void* data = nullptr)
  { return addNodeBack(text, icon, imageIndex, selectedImageIndex, data); }

  //! Adds a new node before the first child node.
  //! \param text text of the new node
  //! \param icon icon text of the new node
  //! \param imageIndex index of the image for the new node (-1 = none)
  //! \param selectedImageIndex index of the selected image for the new node (-1 = same as imageIndex)
  //! \param data user data (void*) of the new node
  //! \param data2 user data2 (IReferenceCounted*) of the new node
  //! \return
  //! returns the new node
  TreeViewItem* addNodeFront(
    const std::string&    text,
    int    icon = -1,
    int          imageIndex = -1,
    int          selectedImageIndex = -1,
    void*        data = nullptr );

  //! Adds a new node behind the other node.
  //! The other node has also te be a child node from this node.
  //! \param text text of the new node
  //! \param icon icon text of the new node
  //! \param imageIndex index of the image for the new node (-1 = none)
  //! \param selectedImageIndex index of the selected image for the new node (-1 = same as imageIndex)
  //! \param data user data (void*) of the new node
  //! \param data2 user data2 (IReferenceCounted*) of the new node
  //! \return
  //! returns the new node or 0 if other is no child node from this
  TreeViewItem* insertNodeAfter(
    TreeViewItem*  other,
    const std::string&    text,
    int    icon = -1,
    int          imageIndex = -1,
    int          selectedImageIndex = -1,
    void*          data = nullptr );

  //! Adds a new node before the other node.
  //! The other node has also te be a child node from this node.
  //! \param text text of the new node
  //! \param icon icon text of the new node
  //! \param imageIndex index of the image for the new node (-1 = none)
  //! \param selectedImageIndex index of the selected image for the new node (-1 = same as imageIndex)
  //! \param data user data (void*) of the new node
  //! \param data2 user data2 (IReferenceCounted*) of the new node
  //! \return
  //! returns the new node or 0 if other is no child node from this
  TreeViewItem* insertNodeBefore(
    TreeViewItem*  other,
    const std::string&    text,
    int    icon = -1,
    int          imageIndex = -1,
    int          selectedImageIndex = -1,
    void*          data = nullptr );

  TreeViewItem* front() const;
  TreeViewItem* back() const;

  void draw(NVGcontext* ctx) override;
  void performLayout(NVGcontext* ctx) override;

  TreeViewItem* prevSibling() const;
  TreeViewItem* nextSibling() const;
  TreeViewItem* nextVisible() const;
  bool deleteNode(TreeViewItem* child);
  bool moveNodeUp(TreeViewItem* child);
  bool moveNodeDown(TreeViewItem* child);
  bool isExpanded() const;
  void setExpanded( bool expanded );
  bool isSelected() const;
  void setSelected( bool selected );
  bool isRoot() const;
  int getLevel() const;
  bool isVisible() const;
  void setColor( const Color& color );
  Color getColor() const { return mFontColor; }
  const std::string& getActiveFont() { return mActiveFont; }

  void removeAllNodes();

  TreeView* view();

private:
  void _init();

  TreeView*  mOwner;
  Widget* mPreviewArea = nullptr; 
  NodeId  mParentId;
  Color mFontColor;
  Vector2i mAnchorPotsition;
  int  mIcon;
  int  mImageIndex;
  int  SelectedImageIndex;
  void*  Data;
  bool mExpanded;
  NodeList mChildrenIds;
  std::string mActiveFont;

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

NAMESPACE_END(nanogui)