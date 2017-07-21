namespace gea {
namespace ren {

// ------------------------------------------------------------------------- //
// render primitives: square                                                 //
// ------------------------------------------------------------------------- //

void create_square(const float size, const color32 color, vertex2_color out_vetices[6]) {
    const float radius = size / 2.0f;
    out_vetices[0].color = color;                   // 0 +----+ 1
    out_vetices[0].position = { -radius, -radius }; //   .\   |
    out_vetices[1].color = color;                   //   . \  |
    out_vetices[1].position = { radius, -radius };  //   .  \ |
    out_vetices[2].color = color;                   //   .   \|
    out_vetices[2].position = { radius, radius };   //   +....+ 2

    out_vetices[3].color = color;                   // 2 +....+
    out_vetices[3].position = { radius, radius };   //   |\   .
    out_vetices[4].color = color;                   //   | \  .
    out_vetices[4].position = { -radius, radius };  //   |  \ .
    out_vetices[5].color = color;                   //   |   \.
    out_vetices[5].position = { -radius, -radius }; // 1 +----+ 0
}

} // namespace ren //
} // namespace gea //
