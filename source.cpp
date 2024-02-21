#include <math.h>

struct Vec{
    float x;
    float y;
};

struct Vec2{
    float x;
    float y;
};

struct AABB
{
  Vec2 min;
  Vec2 max;
};

struct Object{
    Vec2 velocity;
    float mass;
    float restitution;
};

bool AABBvsAABB( AABB a, AABB b )
{
  // Exit with no intersection if found separated along an axis 
  if(a.max.x < b.min.x || a.min.x > b.max.x) return false;
  if(a.max.y < b.min.y || a.min.y > b.max.y) return false;
  // No separating axis found, therefor there is at least one overlapping axis 
  return true;
}

struct Circle
{
  float radius;
  Vec position;
};

bool CirclevsCircle( Circle a, Circle b )
{
  float r = a.radius + b.radius;
  r *= r;
  return r < pow((a.position.x + b.position.x),2) + pow((a.position.y + b.position.y),2);
}

void ResolveCollision( Object A, Object B )
{
  // Calculate relative velocity 
  Vec2 rv;
  rv.x = B.velocity.x - A.velocity.x;
  rv.y = B.velocity.x - A.velocity.y;
  
  // Calculate relative velocity in terms of the normal direction 
  float velAlongNormal = DotProduct( rv, normal )
  // Do not resolve if velocities are separating 
  if(velAlongNormal > 0)
    return;
  // Calculate restitution 
  float e = min( A.restitution, B.restitution)
  // Calculate impulse scalar 
  float j = -(1 + e) * velAlongNormal
  j /= 1 / A.mass + 1 / B.mass
  // Apply impulse 
  Vec2 impulse = j * normal
  A.velocity -= 1 / A.mass * impulse
  B.velocity += 1 / B.mass * impulse
}