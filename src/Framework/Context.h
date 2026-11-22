#pragma once

class AssetManager;

// Non-owning bundle of engine-wide services.
// The services are owned by something that outlives every Scene
// and Entity (currently main()). Entities and Components borrow
// them through this struct, so Framework code never depends on
// game-level types such as Scene.
//
// Keep this limited to services (assets, input, audio, ...).
// World operations (spawn/destroy/find entities) belong elsewhere.
struct Context {
  AssetManager& assets;
};
