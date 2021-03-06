// SPDX-License-Identifier: BSD-2-Clause

// This code is part of the sfizz library and is licensed under a BSD 2-clause
// license. You should have receive a LICENSE.md file along with the code.
// If not, contact the sfizz maintainers at https://github.com/sfztools/sfizz

#pragma once
#include "Effects.h"
#include "Buffer.h"

namespace sfz {
namespace fx {

    /**
     * @brief Effect which does nothing
     */
    class Apan : public Effect {
    public:
        /**
         * @brief Initializes with the given sample rate.
         */
        void setSampleRate(double sampleRate) override;

        /**
         * @brief Sets the maximum number of frames to render at a time. The actual
         * value can be lower but should never be higher.
         */
        void setSamplesPerBlock(int samplesPerBlock) override;

        /**
         * @brief Reset the state to initial.
         */
        void clear() override;

        /**
         * @brief Copy the input signal to the output
         */
        void process(const float* const inputs[], float* const outputs[], unsigned nframes) override;

        /**
          * @brief Instantiates given the contents of the <effect> block.
          */
        static std::unique_ptr<Effect> makeInstance(absl::Span<const Opcode> members);

    private:
        void computeLfos(float* left, float* right, unsigned nframes);
        template <int Wave> void computeLfos(float* left, float* right, unsigned nframes);

    private:
        float _samplePeriod = 0.0;
        sfz::Buffer<float> _lfoOutLeft { config::defaultSamplesPerBlock };
        sfz::Buffer<float> _lfoOutRight { config::defaultSamplesPerBlock };

        // Controls
        float _dry = 0.0;
        float _wet = 0.0;
        float _depth = 0.0;
        int _lfoWave = 0;
        float _lfoFrequency = 0.0;
        float _lfoPhaseOffset = 0.5;

        // State
        float _lfoPhase = 0.0;
    };

} // namespace fx
} // namespace sfz
