#ifndef PIFO_PIPELINE_H_
#define PIFO_PIPELINE_H_

class PIFOPipeline {
 private:
  /// Bank of pipeline stages
  std::vector<PipelineStage> stages_ = {};
};

#endif  // PIFO_PIPELINE_H_
