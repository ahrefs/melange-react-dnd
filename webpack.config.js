const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const outputDir = path.join(__dirname, 'build/');

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './examples/sortable/index.bs.js',
  mode: isProd ? 'production' : 'development',
  output: {
    path: outputDir,
    filename: 'Index.js'
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: 'examples/sortable/index.html',
      inject: false
    })
  ],
  devServer: {
    compress: true,
    static: {
      directory: outputDir,
    },
    port: process.env.PORT || 8000,
    historyApiFallback: true
  }
};
