using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using JayNSon;
using static JayNSon.Func;

namespace SpriteSheetGeneration
{
    public abstract class GeneratorBase : MonoBehaviour
    {
        public abstract IEnumerable<SpriteStamp> Generate();
    }
}