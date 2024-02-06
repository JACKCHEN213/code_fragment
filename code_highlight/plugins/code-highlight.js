(($, hljs) => {
    const cache = {};

    const getDetaultOptions = () => {
        return {
            editable: true,
            default: '',
            language: 'ini',
        };
    }

    const getTextareaElement = (options) => {
        let styles = `position: absolute;
            top: 0;
            left: 0;
            width: calc(100% - 20px);
            height: calc(100% - 20px);
            resize: none;
            background: none;
            z-index: 999;
            color: transparent;
            caret-color: #999;
            font-size: 16px;
            font-weight: 100;
            font-family: '微软雅黑';
            padding: 10px;`;
        return `<textarea id="${options.input_id}" style="${styles}"></textarea>`;
    };

    const getShowElement = (options) => {
        let styles = `position: absolute;
            top: 0px;
            left: 0;
            width: calc(100% - 20px);
            height: calc(100% - 20px);
            z-index: 0;
            font-size: 16px;
            font-weight: 100;
            font-family: '微软雅黑';
            padding: 10px;
            white-space: pre-wrap;`;
        return `<div id="${options.show_id}" class="language-${options.language}" style="${styles}"></div>`;
    };

    const getContentElement = (options) => {
        return `<div id="${options.wrapper_id}" style="position: relative; width: 100%; height: 100%">
                ${getTextareaElement(options)}${getShowElement(options)}
            </div>`;
    };

    const registerEvent = (id) => {
        cache[id].inputElement.off().on('input change', () => {
            cache[id].showElement.html(cache[id].inputElement.val()).removeAttr('data-highlighted');
            hljs.highlightElement(cache[id].showElement.get(0));
        }).val(cache[id].options.default).trigger('change');
    };

    const initCodeHighlight = (options, id) => {
        cache[id] = {
            options: $.extend(
                getDetaultOptions(),
                options,
                {id, input_id: id + '-input', show_id: id+ '-show', wrapper_id: id + '-wrapper'},
            ),
            element: $(`#${id}`),
            inputElement: null,
            showElement: null,
            wrapperElement: null,
        }
        cache[id].element.html(getContentElement(cache[id].options));
        cache[id].inputElement = $(`#${id}-input`);
        cache[id].showElement = $(`#${id}-show`);
        cache[id].wrapperElement = $(`#${id}-wrapper`);
        registerEvent(id);
    };

    $.fn.CodeHighlight = function (options) {
        if (typeof options === 'object') {
            initCodeHighlight(options, this.attr('id'));
        } else if (typeof options === 'string') {
            if (typeof cache[this.attr('id')] === 'undefined') {
                return null;
            }
            if ('getValue' === options) {
                return cache[this.attr('id')].inputElement.val();
            }
            return null;
        }
    }
})(jQuery, hljs);