using System.Drawing;

namespace VerminOS;

public abstract class Component
{
    public Component? Parent { get; }

    public List<Component> Children { get; }

    public uint X { get; set; }

    public uint Y { get; set; }
 
    public uint Width { get; set; }

    public uint Height { get; set; }

    public Color Color { get; set; }

    private readonly uint _originalX, _originalY;

    public Component(Component? parent, uint x, uint y, uint width, uint height, Color color)
    {
        Parent = parent;
        Children = new();
        X = x;
        Y = y;
        Width = width;
        Height = height;
        Color = color;
        _originalX = x;;
        _originalY = y;
    }

    public abstract void Draw();

    public virtual void Update()
    {
        foreach (var child in Children)
        {
            child.X = X + child._originalX;
            child.Y = Y + child._originalY;
            
            child.Draw();
            child.Update();
        }
    }
}