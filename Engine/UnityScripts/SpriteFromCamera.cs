using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using JayNSon;
using static JayNSon.Func;
using UnityEngine.UI;
using UnityEngine.Events;

namespace SpriteSheetGeneration
{
    public class SpriteFromCamera : GeneratorBase
    {
        [Serializable]
        public struct WithOffset<T>
        {
            public T value;
            public float offset;
        }

        public new Camera camera { get => _camera; set => _camera = value; }
        public Vector2Int spriteSize { get => _spriteSize; set => _spriteSize = value; }

        [SerializeField] private Camera _camera;
        [SerializeField] private Vector2Int _spriteSize = new Vector2Int(32, 32);
        [SerializeField] private int _gap = 0;
        [Space]
        [SerializeField, Min(0.01f)] private float _duration;
        [SerializeField, Min(0.01f)] private float _frameRate;
        [SerializeField, Min(1)] private int _frameCount;
        [SerializeField] private bool _useFrameCount;
        [Space]
        [SerializeField] private Animator[] _animators;
        [SerializeField] private WithOffset<ParticleSystem>[] _particleSystems;
        [SerializeField] private UnityEvent _onStart;
        [SerializeField] private UnityEvent<float> _onEach;
        [SerializeField] private UnityEvent _onEnd;
        [Space]
        [SerializeField] private RawImage _preview;

        private RenderTexture _renderTexture;

        private void OnValidate()
        {
            _spriteSize = Max(_spriteSize, new Vector2Int(1, 1));

            TryCreateRenderTexture();

            if (_preview != null)
                _preview.texture = _renderTexture;

            if (_useFrameCount)
                _frameRate = _frameCount / _duration;
            else
                _frameCount = Max(1, RoundToInt(_duration * _frameRate));
        }

        public override IEnumerable<SpriteStamp> Generate()
        {
            if (camera == null)
                yield break;

            TryCreateRenderTexture();

            if (_animators.HasItems())
                foreach (Animator animator in _animators)
                {
                    animator.Rebind();
                    animator.Update(0.0f);
                }

            if (_particleSystems.HasItems())
                foreach (WithOffset<ParticleSystem> particleSystem in _particleSystems)
                {
                    particleSystem.value.Simulate(particleSystem.offset, true, true);
                }

            Vector2Int position = Vector2Int.zero;

            using (TemporaryChange(RenderTexture.active, (v) => RenderTexture.active = v, _renderTexture))
            {
                _onStart?.Invoke();

                for (int i = 0; i < _frameCount; i++)
                {
                    float secondsPerFrame = 1.0f / _frameRate;

                    if (i > 0)
                    {
                        if (_animators.HasItems())
                            foreach (Animator animator in _animators)
                                animator.Update(secondsPerFrame);

                        if (_particleSystems.HasItems())
                            foreach (WithOffset<ParticleSystem> particleSystem in _particleSystems)
                                particleSystem.value.Simulate(secondsPerFrame, true, false);

                        position.x += spriteSize.x + _gap;
                    }

                    _onEach?.Invoke(i * secondsPerFrame);

                    camera.Render();

                    Texture2D pixels = new Texture2D(_renderTexture.width, _renderTexture.height);
                    pixels.ReadPixels(new Rect(0.0f, 0.0f, camera.targetTexture.width, camera.targetTexture.height), 0, 0);

                    yield return new SpriteStamp { pixels = pixels, position = position };
                }

                _onEnd?.Invoke();
            }
        }

        private void TryCreateRenderTexture()
        {
            if (_renderTexture == null || _renderTexture.width != _spriteSize.x || _renderTexture.height != _spriteSize.y)
            {
                if (_renderTexture != null)
                    _renderTexture.Release();

                _renderTexture = new RenderTexture(_spriteSize.x, _spriteSize.y, 16, RenderTextureFormat.ARGB32, RenderTextureReadWrite.sRGB)
                {
                    filterMode = FilterMode.Point
                };
            }

            if (camera != null)
                camera.targetTexture = _renderTexture;
        }
    }
}