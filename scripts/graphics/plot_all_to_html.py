import argparse
import os
import pandas as pd
import plotly.express as px

XTICKS = 40
YTICKS = 20


def plot_queuelevel(queuelevel_log):
    df = pd.read_csv(queuelevel_log, sep=' ', header=None)
    df = df.iloc[:, [0, 19, 22]]
    df.columns = ['s_time', 'queue', 's_size_buffers']

    df['queue'] = df['queue'].apply(lambda s: s.replace("queue=(string)", ""))
    df['s_size_buffers'] = df['s_size_buffers'].apply(lambda s: s.replace(
        "size_buffers=(uint)", "")).apply(lambda s: s.replace(",", ""))
    df['size_buffers'] = pd.to_numeric(df['s_size_buffers'])
    df['time'] = pd.to_datetime(df['s_time'])
    fig = px.line(df, x="time", y="size_buffers", color="queue")
    fig.update_layout(title_text="Queue Level")
    fig.update_xaxes(title_text="Time (s)", nticks=XTICKS)
    fig.update_yaxes(title_text="Queue Level (buffers)", nticks=YTICKS)

    return fig


def plot_thread_cpuusage(thread_cpuusage_log):
    df = pd.read_csv(thread_cpuusage_log, sep=' ', header=None)
    df = df.iloc[:, [0, 19, 21]]
    # rename columns
    df.columns = ['s_time', 'thread_name', 's_cpu_usage']

    df['thread_name'] = df['thread_name'].apply(
        lambda s: s.replace("name=(string)", ""))
    df['s_cpu_usage'] = df['s_cpu_usage'].apply(lambda s: s.replace(
        "usage=(double)", "")).apply(lambda s: s.replace(",", ""))
    df['time'] = pd.to_datetime(df['s_time'])
    df['cpu_usage'] = pd.to_numeric(df['s_cpu_usage'])
    fig = px.line(df, x="time", y="cpu_usage", color="thread_name")
    fig.update_layout(title_text="Thread CPU Usage")
    fig.update_xaxes(title_text="Time (s)", nticks=XTICKS)
    fig.update_yaxes(title_text="CPU Usage (%)", nticks=YTICKS)
    return fig


def plot_framerate(framerate_log):
    df = pd.read_csv(framerate_log, sep=' ', header=None)

    df = df.iloc[:, [0, 19, 20]]
    # rename columns
    df.columns = ['s_time', 'pad', 's_framerate']
    df['time'] = pd.to_datetime(df['s_time'])
    df['pad'] = df['pad'].apply(lambda s: s.replace("pad=(string)", ""))
    df['s_framerate'] = df['s_framerate'].apply(lambda s: s.replace(
        "fps=(uint)", "")).apply(lambda s: s.replace(";", ""))
    df['framerate'] = pd.to_numeric(df['s_framerate'])
    fig = px.line(df, x="time", y="framerate", color="pad")
    fig.update_layout(title_text="Framerate")
    fig.update_xaxes(title_text="Time (s)", nticks=XTICKS)
    fig.update_yaxes(title_text="Framerate (fps)", nticks=YTICKS)
    return fig


def plot_bitrate(bitrate_log):
    df = pd.read_csv(bitrate_log, sep=' ', header=None)

    df = df.iloc[:, [0, 19, 20]]
    # rename columns
    df.columns = ['s_time', 'pad', 's_bitrate']
    df['time'] = pd.to_datetime(df['s_time'])
    df['pad'] = df['pad'].apply(lambda s: s.replace("pad=(string)", ""))
    df['s_bitrate'] = df['s_bitrate'].apply(lambda s: s.replace(
        "bitrate=(guint64)", "")).apply(lambda s: s.replace(";", ""))
    df['bitrate'] = pd.to_numeric(df['s_bitrate'])
    fig = px.line(df, x="time", y="bitrate", color="pad")
    fig.update_layout(title_text="Bitrate")
    fig.update_xaxes(title_text="Time (s)", nticks=XTICKS)
    fig.update_yaxes(title_text="Bitrate (bps)", nticks=YTICKS)
    return fig


def plot_cpuusage(cpuusage_log):
    df = pd.read_csv(cpuusage_log, sep=' ', header=None)
    df = df.iloc[:, [0, 19, 20]]
    # rename columns
    df.columns = ['s_time', 'core', 's_cpu_usage']

    df['core'] = df['core'].apply(
        lambda s: s.replace("number=(uint)", ""))
    df['s_cpu_usage'] = df['s_cpu_usage'].apply(lambda s: s.replace(
        "load=(double)", "")).apply(lambda s: s.replace(";", ""))
    df['time'] = pd.to_datetime(df['s_time'])
    df['cpu_usage'] = pd.to_numeric(df['s_cpu_usage'])
    fig = px.line(df, x="time", y="cpu_usage", color="core")
    fig.update_layout(title_text="CPU Usage")
    fig.update_xaxes(title_text="Time (s)", nticks=XTICKS)
    fig.update_yaxes(title_text="CPU Usage (%)", nticks=YTICKS)
    return fig


def plot_interlatency(interlatency_log):
    df = pd.read_csv(interlatency_log, sep=' ', header=None)
    df = df.iloc[:, [0, 20, 21]]
    # rename columns
    df.columns = ['s_time', 'destination_pad', 's_proctime']

    df['destination_pad'] = df['destination_pad'].apply(
        lambda s: s.replace("to_pad=(string)", ""))
    df['s_proctime'] = df['s_proctime'].apply(lambda s: s.replace(
        "time=(string)", "")).apply(lambda s: s.replace(";", ""))

    df['proctime'] = pd.to_datetime(df['s_proctime'])
    df['time'] = pd.to_datetime(df['s_time'])
    fig = px.line(df, x="time", y="proctime", color="destination_pad")
    fig.update_layout(title_text="Interlatency")
    fig.update_xaxes(title_text="Time (s)", nticks=XTICKS)
    fig.update_yaxes(title_text="Time (s)", nticks=YTICKS)
    return fig


def plot_proctime(proctime_log):
    df = pd.read_csv(proctime_log, sep=' ', header=None)
    df = df.iloc[:, [0, 19, 20]]
    # rename columns
    df.columns = ['s_time', 'element', 's_proctime']

    df['element'] = df['element'].apply(
        lambda s: s.replace("element=(string)", ""))
    df['s_proctime'] = df['s_proctime'].apply(lambda s: s.replace(
        "time=(string)", "")).apply(lambda s: s.replace(";", ""))

    df['proctime'] = pd.to_datetime(df['s_proctime'])
    df['time'] = pd.to_datetime(df['s_time'])
    fig = px.line(df, x="time", y="proctime", color="element")
    fig.update_xaxes(nticks=XTICKS)
    fig.update_layout(title_text="Processing Time")
    fig.update_xaxes(title_text="Time (s)", nticks=XTICKS)
    fig.update_yaxes(title_text="Processing Time (s)", nticks=YTICKS)
    return fig


def plot_scheduletime(scheduletime_log):
    df = pd.read_csv(scheduletime_log, sep=' ', header=None)
    df = df.iloc[:, [0, 19, 20]]
    # rename columns
    df.columns = ['s_time', 'pad', 's_scheduletime']

    df['pad'] = df['pad'].apply(
        lambda s: s.replace("pad=(string)", ""))
    df['s_scheduletime'] = df['s_scheduletime'].apply(lambda s: s.replace(
        "time=(string)", "")).apply(lambda s: s.replace(";", ""))

    df['scheduletime'] = pd.to_datetime(df['s_scheduletime'])
    df['time'] = pd.to_datetime(df['s_time'])
    fig = px.line(df, x="time", y="scheduletime", color="pad")
    fig.update_xaxes(nticks=XTICKS)
    fig.update_layout(title_text="Schedule Time")
    fig.update_xaxes(title_text="Time (s)", nticks=XTICKS)
    fig.update_yaxes(title_text="Schedule Time(s)", nticks=YTICKS)
    return fig


def main():

    # use Argparser
    parser = argparse.ArgumentParser(description='Plot traces')
    # add argument to hold path of traces dir
    parser.add_argument('-p','--path', type=str, help='Path to traces dir')

    args = parser.parse_args()
    traces_dir = args.path

    # get list of files in traces dir
    trace_log_files = os.listdir(traces_dir)

    with open(f"{traces_dir}/graphs.html", 'a') as f:
        if 'threadmonitor.log' in trace_log_files:
            f.write(plot_thread_cpuusage(
                traces_dir + '/threadmonitor.log').to_html(full_html=False, include_plotlyjs='cdn'))
        if 'queuelevel.log' in trace_log_files:
            f.write(plot_queuelevel(
                traces_dir + '/queuelevel.log').to_html(full_html=False, include_plotlyjs='cdn'))
        if 'bitrate.log' in trace_log_files:
            f.write(plot_bitrate(
                traces_dir + '/bitrate.log').to_html(full_html=False, include_plotlyjs='cdn'))
        if 'cpuusage.log' in trace_log_files:
            f.write(plot_cpuusage(
                traces_dir + '/cpuusage.log').to_html(full_html=False, include_plotlyjs='cdn'))
        if 'interlatency.log' in trace_log_files:
            f.write(plot_interlatency(
                traces_dir + '/interlatency.log').to_html(full_html=False, include_plotlyjs='cdn'))
        if 'proctime.log' in trace_log_files:
            f.write(plot_proctime(
                traces_dir + '/proctime.log').to_html(full_html=False, include_plotlyjs='cdn'))
        if 'scheduletime.log' in trace_log_files:
            f.write(plot_scheduletime(
                traces_dir + '/scheduletime.log').to_html(full_html=False, include_plotlyjs='cdn'))
        if 'framerate.log' in trace_log_files:
            f.write(plot_framerate(
                traces_dir + '/framerate.log').to_html(full_html=False, include_plotlyjs='cdn'))


if __name__ == "__main__":
    main()
