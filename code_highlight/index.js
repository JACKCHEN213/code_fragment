import rehype from 'rehype'
import rehypePrism from 'rehype-prism-plus'

rehype().use(rehypePrism).process(/* some html */)