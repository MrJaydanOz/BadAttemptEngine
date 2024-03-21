using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using JayNSon;
using static JayNSon.Func;

namespace SpriteSheetGeneration
{
    [ExecuteAlways]
    public class ModifyCameraMatrix : MonoBehaviour
    {
        [SerializeField] private Camera[] _cameras;
        [SerializeField] private Matrix4x4 _matrix;
        [SerializeField] private bool _read;
        [SerializeField] private bool _update;

        private void OnValidate()
        {
            if (_update)
                DoUpdate();
        }

        private void Update()
        {
            if (_update)
                DoUpdate();
        }

        private void DoUpdate()
        {
            if (_cameras.HasItems())
            {
                if (_read)
                {
                    _read = false;
                    _matrix = _cameras[0].projectionMatrix;
                }
                else
                {
                    foreach (Camera camera in _cameras)
                        camera.projectionMatrix = _matrix;
                }
            }
        }
    }
}