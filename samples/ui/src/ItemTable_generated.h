// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_ITEMTABLE_HOPE_SAMPLES_UI_FBS_H_
#define FLATBUFFERS_GENERATED_ITEMTABLE_HOPE_SAMPLES_UI_FBS_H_

#include "flatbuffers/flatbuffers.h"


namespace hope {
namespace samples {
namespace ui {
namespace fbs {

struct Item;
struct ItemTable;

struct Item FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  int32_t id() const { return GetField<int32_t>(4, 0); }
  const flatbuffers::String *label() const { return GetPointer<const flatbuffers::String *>(6); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, 4 /* id */) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 6 /* label */) &&
           verifier.Verify(label()) &&
           verifier.EndTable();
  }
};

struct ItemBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(int32_t id) { fbb_.AddElement<int32_t>(4, id, 0); }
  void add_label(flatbuffers::Offset<flatbuffers::String> label) { fbb_.AddOffset(6, label); }
  ItemBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  ItemBuilder &operator=(const ItemBuilder &);
  flatbuffers::Offset<Item> Finish() {
    auto o = flatbuffers::Offset<Item>(fbb_.EndTable(start_, 2));
    return o;
  }
};

inline flatbuffers::Offset<Item> CreateItem(flatbuffers::FlatBufferBuilder &_fbb,
   int32_t id = 0,
   flatbuffers::Offset<flatbuffers::String> label = 0) {
  ItemBuilder builder_(_fbb);
  builder_.add_label(label);
  builder_.add_id(id);
  return builder_.Finish();
}

struct ItemTable FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  const flatbuffers::Vector<flatbuffers::Offset<Item>> *items() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Item>> *>(4); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* items */) &&
           verifier.Verify(items()) &&
           verifier.VerifyVectorOfTables(items()) &&
           verifier.EndTable();
  }
};

struct ItemTableBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_items(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Item>>> items) { fbb_.AddOffset(4, items); }
  ItemTableBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  ItemTableBuilder &operator=(const ItemTableBuilder &);
  flatbuffers::Offset<ItemTable> Finish() {
    auto o = flatbuffers::Offset<ItemTable>(fbb_.EndTable(start_, 1));
    return o;
  }
};

inline flatbuffers::Offset<ItemTable> CreateItemTable(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Item>>> items = 0) {
  ItemTableBuilder builder_(_fbb);
  builder_.add_items(items);
  return builder_.Finish();
}

inline const ItemTable *GetItemTable(const void *buf) { return flatbuffers::GetRoot<ItemTable>(buf); }

inline bool VerifyItemTableBuffer(flatbuffers::Verifier &verifier) { return verifier.VerifyBuffer<ItemTable>(); }

inline void FinishItemTableBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<ItemTable> root) { fbb.Finish(root); }

}  // namespace fbs
}  // namespace ui
}  // namespace samples
}  // namespace hope

#endif  // FLATBUFFERS_GENERATED_ITEMTABLE_HOPE_SAMPLES_UI_FBS_H_
