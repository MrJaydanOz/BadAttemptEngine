using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using JayNSon;
using static JayNSon.Func;
using System.IO;
using JayNSon.UI;
using System.Linq;


#if UNITY_EDITOR
using UnityEngine.UIElements;
using UnityEditor;
using UnityEditor.UIElements;
#endif

namespace SpriteSheetGeneration
{
    public class SpriteSheetGenerator : GeneratorBase
    {
        public FlexContainer.Direction stackDirection { get => _stackDirection; set => _stackDirection = value; }
        public int gap { get => _gap; set => _gap = value; }
        public bool alignEnd { get => _alignEnd; set => _alignEnd = value; }
        public Vector2Int offset { get => _offset; set => _offset = value; }

        [SerializeField] private FlexContainer.Direction _stackDirection;
        [SerializeField] private bool _alignEnd;
        [SerializeField] private int _gap;
        [SerializeField] private Vector2Int _offset;

        [SerializeField] private bool _create;

        private void Update()
        {
            if (_create)
            {
                _create = false;
#if UNITY_EDITOR
                StartCoroutine(Create());
#endif
            }
        }

        public override IEnumerable<SpriteStamp> Generate()
        {
            List<GeneratorBase> generators = new List<GeneratorBase>();

            foreach (Transform child in transform)
                if (child.TryGetComponent(out GeneratorBase generator))
                    generators.Add(generator);

            if (!generators.HasItems())
                return AnEmptyEnumerable<SpriteStamp>();

            List<SpriteStamp> stamps = new List<SpriteStamp>();

            int c = generators.Count;
            switch (_stackDirection)
            {
                case FlexContainer.Direction.Row:
                {
                    int positionSoFar = 0;

                    for (int i = 0; i < c; i++)
                    {
                        IEnumerable<SpriteStamp> generatorStamps = generators[i].Generate();

                        RangeValue<Vector2Int> size =
                            generatorStamps
                            .Select((s) => new RangeValue<Vector2Int>(s.position, s.position + new Vector2Int(s.pixels.width, s.pixels.height)))
                            .Aggregate((a, b) => new RangeValue<Vector2Int>(Min(a.min, b.min), Max(a.max, b.max)));

                        if (_alignEnd)
                            stamps.AddRange(generatorStamps.Select((s) => new SpriteStamp() { pixels = s.pixels, position = s.position - size.min + new Vector2Int(positionSoFar, size.min.y - size.max.y) }));
                        else
                            stamps.AddRange(generatorStamps.Select((s) => new SpriteStamp() { pixels = s.pixels, position = s.position - size.min + new Vector2Int(positionSoFar, 0) }));

                        positionSoFar += size.max.x - size.min.x + _gap;
                    }
                    break;
                }
                case FlexContainer.Direction.RowReverse:
                {
                    int positionSoFar = 0;

                    for (int i = 0; i < c; i++)
                    {
                        IEnumerable<SpriteStamp> generatorStamps = generators[c - i - 1].Generate();

                        RangeValue<Vector2Int> size =
                            generatorStamps
                            .Select((s) => new RangeValue<Vector2Int>(s.position, s.position + new Vector2Int(s.pixels.width, s.pixels.height)))
                            .Aggregate((a, b) => new RangeValue<Vector2Int>(Min(a.min, b.min), Max(a.max, b.max)));

                        if (_alignEnd)
                            stamps.AddRange(generatorStamps.Select((s) => new SpriteStamp() { pixels = s.pixels, position = s.position - size.min + new Vector2Int(positionSoFar, size.min.y - size.max.y) }));
                        else
                            stamps.AddRange(generatorStamps.Select((s) => new SpriteStamp() { pixels = s.pixels, position = s.position - size.min + new Vector2Int(positionSoFar, 0) }));

                        positionSoFar += size.max.x - size.min.x + _gap;
                    }
                    break;
                }
                case FlexContainer.Direction.Column:
                {
                    int positionSoFar = 0;

                    for (int i = 0; i < c; i++)
                    {
                        IEnumerable<SpriteStamp> generatorStamps = generators[i].Generate();

                        RangeValue<Vector2Int> size =
                            generatorStamps
                            .Select((s) => new RangeValue<Vector2Int>(s.position, s.position + new Vector2Int(s.pixels.width, s.pixels.height)))
                            .Aggregate((a, b) => new RangeValue<Vector2Int>(Min(a.min, b.min), Max(a.max, b.max)));

                        if (_alignEnd)
                            stamps.AddRange(generatorStamps.Select((s) => new SpriteStamp() { pixels = s.pixels, position = s.position - size.min + new Vector2Int(size.min.x - size.max.x, positionSoFar) }));
                        else
                            stamps.AddRange(generatorStamps.Select((s) => new SpriteStamp() { pixels = s.pixels, position = s.position - size.min + new Vector2Int(0, positionSoFar) }));

                        positionSoFar += size.max.y - size.min.y + _gap;
                    }
                    break;
                }
                case FlexContainer.Direction.ColumnReverse:
                {
                    int positionSoFar = 0;

                    for (int i = 0; i < c; i++)
                    {
                        IEnumerable<SpriteStamp> generatorStamps = generators[c - i - 1].Generate();

                        RangeValue<Vector2Int> size =
                            generatorStamps
                            .Select((s) => new RangeValue<Vector2Int>(s.position, s.position + new Vector2Int(s.pixels.width, s.pixels.height)))
                            .Aggregate((a, b) => new RangeValue<Vector2Int>(Min(a.min, b.min), Max(a.max, b.max)));

                        if (_alignEnd)
                            stamps.AddRange(generatorStamps.Select((s) => new SpriteStamp() { pixels = s.pixels, position = s.position - size.min + new Vector2Int(size.min.x - size.max.x, positionSoFar) }));
                        else
                            stamps.AddRange(generatorStamps.Select((s) => new SpriteStamp() { pixels = s.pixels, position = s.position - size.min + new Vector2Int(0, positionSoFar) }));

                        positionSoFar += size.max.y - size.min.y + _gap;
                    }
                    break;
                }
                default:
                    throw new InvalidEnumValueException<FlexContainer.Direction>();
            }

            return stamps;
        }

#if UNITY_EDITOR
        public IEnumerator Create()
        {
            yield return new WaitForEndOfFrame();

            IEnumerable<SpriteStamp> stamps = Generate();

            if (!stamps.HasItems())
                yield break;

            RangeValue<Vector2Int> size =
                stamps
                .Select((s) => new RangeValue<Vector2Int>(s.position, s.position + new Vector2Int(s.pixels.width, s.pixels.height)))
                .Aggregate((a, b) => new RangeValue<Vector2Int>(Min(a.min, b.min), Max(a.max, b.max)));

            Texture2D canvas = new Texture2D(size.max.x - size.min.x, size.max.y - size.min.y);

            Color32 clear = new Color32(0, 0, 0, 0);
            canvas.SetPixels32(CreateArray(canvas.width * canvas.height, (i) => clear));

            foreach (SpriteStamp stamp in stamps)
                canvas.SetPixels32(stamp.position.x, stamp.position.y, stamp.pixels.width, stamp.pixels.height, stamp.pixels.GetPixels32());

            string filePath = Application.dataPath + "/Results";
            Directory.CreateDirectory(filePath);

            File.WriteAllBytes($"{filePath}/SpriteSheet{RandomEngine.UnityDefault.Range(1000, 9999)}.png", canvas.EncodeToPNG());

            AssetDatabase.Refresh();
        }

        /*
        [CustomEditor(typeof(SpriteSheetGenerator))]
        [CanEditMultipleObjects]
        private class Drawer : Editor
        {
            public override VisualElement CreateInspectorGUI()
            {
                var root = new VisualElement();

                SpriteSheetGenerator generator = (SpriteSheetGenerator)target;

                root.Add(new PropertyField(serializedObject.FindProperty("_offset"), "Offset"));

                Foldout foldout = new Foldout();
                foldout.text = ;
                root.Add();

                var rect = new VisualElement();
                rect.style.backgroundColor = Color.blue;
                rect.style.width = new Length(100.0f, LengthUnit.Percent);
                rect.style.height = 50.0f;

                root.Add(rect);

                return root;
            }
        }
        */
#endif
    }
}